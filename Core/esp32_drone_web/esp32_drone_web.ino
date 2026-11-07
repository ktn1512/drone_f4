/* ESP32 DevKit - Web drone controller: luon mode 2 (ALT_HOLD) cua STM32.
 * Bench-test KHONG gan canh quat truoc khi bay. */
#include <Arduino.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WebServer.h>
#include <math.h>
#include "index_html.h"

constexpr char WIFI_SSID[] = "DESKTOP-7F2FABB 9674";
constexpr char WIFI_PASS[] = "khanhkhanh";

constexpr int E220_RX = 16;
constexpr int E220_TX = 17;
constexpr int E220_M0 = 25;
constexpr int E220_M1 = 26;
constexpr int E220_AUX = 27; // -1 neu khong noi AUX
constexpr uint32_t UART_BAUD = 9600;

constexpr uint16_t MIN_THR = 1000;
constexpr uint16_t MAX_THR = 1700;
constexpr uint16_t MAX_MOTOR_STATUS_US = 2000;
constexpr uint16_t AUTO_REFERENCE_US = 1400; // STM32 mode 2 bat buoc = 1400

constexpr int16_t MAX_ROLL_PITCH_DEG = 12; // STM32 cho toi da 15
constexpr int16_t MAX_YAW_DPS = 60;        // STM32 cho toi da 90

// ---- Master-slave timing (9600 baud / air 2.4k) - giao thuc v2 ----
// T ~25-36 byte; tra loi S/G/M <= 55 byte (truoc day S ~86-120 byte, RTT ~1185 ms).
// Timeout PHAI lon hon RTT xau nhat (xem "RTTmax=" tren Serial), neu khong
// ESP se phat chong len luc STM dang tra loi. Neu RTTmax > ~1000 ms thi
// tang REPLY_TIMEOUT_MS va cap nhat lai 2 hang so ben STM32.
// Rang buoc voi STM32 (drone_link.h / main.c):
//   REPLY_TIMEOUT_MS + POLL_GUARD_MS + ~26 ms day T < DRONE_LINK_CLIMB_TIMEOUT_MS (1600)
//   2 x (REPLY_TIMEOUT_MS + 46) < LINK_LOST_MS (3000) -> mat 2 phien lien tiep
//   khong kich failsafe, mat 3 phien (~4 s) moi kich.
constexpr uint32_t REPLY_TIMEOUT_MS = 1300;
constexpr uint32_t POLL_GUARD_MS = 20; // nghi sau moi phien truoc khi phat tiep

constexpr uint32_t STATUS_VALID_MS = 5000;
constexpr uint32_t COMMAND_HEARTBEAT_MS = 1500; // trinh duyet im -> lenh ve 0 (giu do cao)
constexpr uint32_t WEB_LOST_LAND_MS = 10000;    // dang bay ma mat trinh duyet 10 s -> DUNG
constexpr int16_t WEB_LOST_LAND_CLIMB = -60;    // giong FAILSAFE_CLIMB ben STM32
constexpr uint32_t AUX_SETTLE_MS = 3;
constexpr uint32_t RX_PARTIAL_TIMEOUT_MS = 1200;
constexpr uint32_t WIFI_RETRY_MS = 10000;
constexpr size_t MAX_RADIO_PACKET_BYTES = 200;

// Ly do STM32 tat ALT_HOLD (truong cuoi goi S). Khop AltExitReason_t trong drone_link.h.
enum AltExit : uint8_t
{
  ALT_EXIT_NONE = 0,
  ALT_EXIT_LANDED = 1, // ha canh binh thuong -> KHONG DUNG
  ALT_EXIT_BARO = 2,
  ALT_EXIT_BARO_LATCHED = 3,
  ALT_EXIT_UPDATE_FAULT = 4,
  ALT_EXIT_FAILSAFE_LANDED = 5,
  ALT_EXIT_STOPPED = 6,
  // ALT_EXIT_MAX = ALT_EXIT_STOPPED
  ALT_EXIT_EMERG_LANDED = 7, // ha canh khan cap (baro loi) da xong, motor 1000
  ALT_EXIT_IMU = 8,          // mat IMU, STM da cat motor
  ALT_EXIT_TAKEOFF_FAIL = 9, // het gio cat canh ma khong roi dat
  ALT_EXIT_MAX = ALT_EXIT_TAKEOFF_FAIL
};

// Trang thai truc dung STM32 (truong fs goi S). Khop FlightState_t (flight_mode.h).
enum FlightState : uint8_t
{
  FS_DISARMED = 0,
  FS_SPOOLUP = 1,
  FS_TAKEOFF = 2,
  FS_ALT_HOLD = 3,
  FS_LANDING = 4,
  FS_SPOOLDOWN = 5,
  FS_EMERGENCY = 6,
  FS_MAX = FS_EMERGENCY
};

const char *flightStateText(uint8_t fs)
{
  switch (fs)
  {
  case FS_DISARMED:
    return "Dung motor";
  case FS_SPOOLUP:
    return "Dang tang ga khoi dong";
  case FS_TAKEOFF:
    return "Dang cat canh";
  case FS_ALT_HOLD:
    return "Giu do cao";
  case FS_LANDING:
    return "Dang ha";
  case FS_SPOOLDOWN:
    return "Ha ga ve idle";
  case FS_EMERGENCY:
    return "Ha khan cap (baro loi)";
  default:
    return "Khong ro";
  }
}

// "Active" = motor dang chay co dieu khien (giong FlightMode_Active ben STM32).
bool flightStateActive(uint8_t fs)
{
  return fs == FS_SPOOLUP || fs == FS_TAKEOFF || fs == FS_ALT_HOLD ||
         fs == FS_LANDING || fs == FS_EMERGENCY;
}

const char *altExitText(uint8_t reason)
{
  switch (reason)
  {
  case ALT_EXIT_NONE:
    return "";
  case ALT_EXIT_LANDED:
    return "Da ha canh";
  case ALT_EXIT_BARO:
    return "Loi baro DPS310";
  case ALT_EXIT_BARO_LATCHED:
    return "Loi baro DPS310 (da chot)";
  case ALT_EXIT_UPDATE_FAULT:
    return "Loi mau do cao (AltitudeHold_Update)";
  case ALT_EXIT_FAILSAFE_LANDED:
    return "Mat link, failsafe da ha canh";
  case ALT_EXIT_STOPPED:
    return "Da DUNG";
  case ALT_EXIT_EMERG_LANDED:
    return "Ha canh khan cap (baro loi) da xong";
  case ALT_EXIT_IMU:
    return "Mat IMU, da cat motor";
  case ALT_EXIT_TAKEOFF_FAIL:
    return "Cat canh that bai (khong roi dat)";
  default:
    return "Khong ro";
  }
}

WebServer web(80);
HardwareSerial LoRa(2);

// ---- Trang thai dieu khien ----
bool stopped = false; // DUNG khan cap: gui T,seq,1000 (mode 0) cho toi khi KICH HOAT LAI
String stopReason = "";
bool altWasActive = false;     // tung nhan ALT_ACTIVE=1 (dang bay)
bool webLostLanding = false;   // mat trinh duyet khi dang bay: dang tu ha
bool faultStopPending = false; // STM bao loi giua troi: chi DUNG khi STM da ve ga 1000
String faultText = "";

int16_t climbCommand = 0, rollCommand = 0, pitchCommand = 0, yawRateCommand = 0;
uint32_t lastWebMs = 0, lastCmdMs = 0;
uint32_t nextSeq = 1;

// ---- Telemetry tu STM32 ----
bool statusSeen = false;
uint32_t lastStatusMs = 0;
uint32_t validStatusCount = 0, invalidStatusCount = 0;
String statusDiagnostic = "Chua nhan status S hop le";
uint16_t rxThrottle = MIN_THR; // ga THAT cua STM32 (khong phai so nhac lai lenh T)
uint8_t rxAltExit = ALT_EXIT_NONE;
float rxRoll = 0, rxPitch = 0, rxYaw = 0;
bool rxAltActive = false;
uint8_t rxFlightState = FS_DISARMED;
// Chan doan tu goi M (bo dem phia STM32).
bool diagSeen = false;
unsigned long diagStmRxT = 0, diagStmRxBad = 0, diagStmLate = 0, diagStmUartErr = 0, diagStmRxOvf = 0;
float rxAltitudeM = 0;
bool rxGpsFix = false;
double rxGpsLat = 0, rxGpsLon = 0;
float rxGpsSpeedKmh = 0, rxGpsCourseDeg = 0;
unsigned rxGpsSatellites = 0;
uint16_t rxMotors[4] = {1000, 1000, 1000, 1000};

// ---- Radio ----
char rxLine[176];
size_t rxLength = 0;
bool rxDiscard = false;
uint32_t lastRxByteMs = 0;
bool radioStarted = false;
bool auxWasHigh = false;
uint32_t auxHighSinceMs = 0;
uint32_t radioTxCount = 0, radioRxCount = 0, radioRxByteCount = 0;
uint32_t radioRxErrors = 0, radioTxErrors = 0;
uint32_t lastRadioRxMs = 0;
String lastRadioRx, lastRadioTx;

// ---- Master state ----
enum class LinkState : uint8_t
{
  IDLE,
  WAIT_REPLY
};
LinkState linkState = LinkState::IDLE;
uint32_t pendingSeq = 0;
uint32_t pollSentMs = 0, pollDoneMs = 0, lastRttMs = 0, maxRttMs = 0;
uint32_t replyOkCount = 0, replyTimeoutCount = 0, replyMismatchCount = 0;

// JSON string: chi giu ASCII an toan, byte la thi escape.
String jsonString(const String &value)
{
  String out;
  out.reserve(value.length() + 2);
  out += '"';
  for (size_t i = 0; i < value.length(); ++i)
  {
    const uint8_t c = static_cast<uint8_t>(value[i]);
    if (c == '"' || c == '\\')
    {
      out += '\\';
      out += static_cast<char>(c);
    }
    else if (c < 0x20 || c >= 0x7F)
    {
      char hex[7];
      snprintf(hex, sizeof(hex), "\\u%04X", static_cast<unsigned>(c));
      out += hex;
    }
    else
    {
      out += static_cast<char>(c);
    }
  }
  out += '"';
  return out;
}

uint8_t xorChecksum(const String &s)
{
  uint8_t v = 0;
  for (size_t i = 0; i < s.length(); i++)
    v ^= uint8_t(s[i]);
  return v;
}

String frameOf(const String &payload)
{
  char hex[5];
  snprintf(hex, sizeof(hex), "*%02X\n", xorChecksum(payload));
  return payload + hex;
}

bool decodeFrame(String &raw)
{
  if (raw.length() < 4 || raw[raw.length() - 3] != '*')
    return false;
  String hex = raw.substring(raw.length() - 2);
  char *end = nullptr;
  unsigned long want = strtoul(hex.c_str(), &end, 16);
  if (end != hex.c_str() + 2 || want > 255)
    return false;
  raw.remove(raw.length() - 3);
  return xorChecksum(raw) == want;
}

bool radioAuxReady(uint32_t now)
{
  if (E220_AUX < 0)
    return true;
  if (digitalRead(E220_AUX) == LOW)
  {
    auxWasHigh = false;
    return false;
  }
  if (!auxWasHigh)
  {
    auxWasHigh = true;
    auxHighSinceMs = now;
  }
  return (uint32_t)(now - auxHighSinceMs) >= AUX_SETTLE_MS;
}

bool radioReady(uint32_t now)
{
  return radioStarted && radioAuxReady(now);
}

bool sendRadioBytes(const String &packet, const String &description)
{
  uint32_t now = millis();
  if (!radioReady(now))
    return false;
  if (packet.length() == 0 || packet.length() > MAX_RADIO_PACKET_BYTES)
  {
    ++radioTxErrors;
    return false;
  }
  const size_t written = LoRa.write(
      reinterpret_cast<const uint8_t *>(packet.c_str()), packet.length());
  LoRa.flush(true); // cho UART day het vao E220 (~15 ms voi goi T)
  if (written != packet.length())
  {
    ++radioTxErrors;
    Serial.println("E220 UART write failed");
    return false;
  }
  ++radioTxCount;
  lastRadioTx = description;
  Serial.print("TX > ");
  Serial.println(description);
  return true;
}

bool sendRadio(const String &payload)
{
  return sendRadioBytes(frameOf(payload), payload);
}

// ---- Goi T ----
// Binh thuong : T,seq,1400,2,climb,roll,pitch,yaw   (STM32 mode 2: cat canh + giu do cao)
// DUNG        : T,seq,1000                          (STM32 mode 0, motor 1000 us)
String makeThrottlePayload(uint32_t seq)
{
  if (stopped)
    return "T," + String(seq) + "," + String(MIN_THR);
  return "T," + String(seq) + "," + String(AUTO_REFERENCE_US) + ",2," + String(climbCommand) + "," + String(rollCommand) + "," + String(pitchCommand) + "," + String(yawRateCommand);
}

void endPoll(uint32_t now)
{
  linkState = LinkState::IDLE;
  pollDoneMs = now;
}

bool sendThrottleFrame()
{
  const uint32_t seq = nextSeq;
  if (!sendRadio(makeThrottlePayload(seq)))
    return false;
  ++nextSeq;
  pendingSeq = seq;
  pollSentMs = millis();
  linkState = LinkState::WAIT_REPLY;
  return true;
}

// Master luon gui lenh moi nhat o phien ke tiep -> khong can ep gui.
void forceTxSoon() {}

void processRadioTx()
{
  const uint32_t now = millis();
  if (!stopped)
  {
    if (!webLostLanding && (climbCommand || rollCommand || pitchCommand || yawRateCommand) &&
        (uint32_t)(now - lastCmdMs) > COMMAND_HEARTBEAT_MS)
    {
      zeroCommands();
    }
    // Mat trinh duyet khi dang bay: KHONG gui mode 0 (se cat motor giua troi).
    // Gui lenh XUONG de STM32 tu ha va tu disarm khi cham dat (ALT_EXIT_LANDED).
    if (altWasActive && !webLostLanding && (uint32_t)(now - lastWebMs) > WEB_LOST_LAND_MS)
    {
      webLostLanding = true;
    }
    if (webLostLanding)
    {
      climbCommand = WEB_LOST_LAND_CLIMB;
      rollCommand = pitchCommand = yawRateCommand = 0;
    }
  }

  // Phan gui T phai chay CA KHI stopped (de phat T,seq,1000 = DUNG).
  if (linkState == LinkState::WAIT_REPLY)
  {
    if ((uint32_t)(now - pollSentMs) >= REPLY_TIMEOUT_MS)
    {
      // Chi sau timeout moi chac STM khong con phat -> moi duoc phat tiep.
      ++replyTimeoutCount;
      endPoll(now);
    }
    return;
  }
  if ((uint32_t)(now - pollDoneMs) < POLL_GUARD_MS)
    return;
  if (rxLength > 0)
    return; // dang co frame do dang tren UART
  if (!radioReady(now))
    return; // AUX ESP LOW: module dang ban
  (void)sendThrottleFrame();
}

void zeroCommands()
{
  if (climbCommand || rollCommand || pitchCommand || yawRateCommand)
  {
    climbCommand = rollCommand = pitchCommand = yawRateCommand = 0;
    forceTxSoon();
  }
}

void stopNow(const char *reason)
{
  stopped = true;
  altWasActive = false;
  webLostLanding = false;
  faultStopPending = false;
  stopReason = reason;
  climbCommand = rollCommand = pitchCommand = yawRateCommand = 0;
  forceTxSoon();
  Serial.print("STOP: ");
  Serial.println(reason);
}

bool freshStatus()
{
  return statusSeen && (uint32_t)(millis() - lastStatusMs) <= STATUS_VALID_MS;
}

void respondOk()
{
  web.send(200, "application/json", "{\"ok\":true}");
}

void respondError(const String &reason, int status = 400)
{
  web.send(status, "application/json",
           "{\"ok\":false,\"error\":" + jsonString(reason) + "}");
}

bool parseSigned(const String &s, int minVal, int maxVal, int16_t *value)
{
  if (!s.length())
    return false;
  char *end = nullptr;
  long n = strtol(s.c_str(), &end, 10);
  if (end == s.c_str() || *end || n < minVal || n > maxVal)
    return false;
  *value = static_cast<int16_t>(n);
  return true;
}

// ---- Goi tra loi tu STM32 (giao thuc v2) ----
// S,seq,thr,roll10,pitch10,yaw,fs,alt_cm,exit   (trang thai dieu khien)
// G,seq,fix,lat,lon,speed10_kmh,course,sats     (GPS, 1/5 phien)
// M,seq,m1,m2,m3,m4,rxT,rxBad,late,uerr,rxovf   (motor + chan doan, 1/5 phien)
// thr = ga that dang ra mixer.

// Xu ly logic an toan khi nhan S hop le (tach rieng tu onFrame cu, giu nguyen hanh vi).
void applyStatusS(unsigned thr, int roll10, int pitch10, int yaw, unsigned fs,
                  int altCm, unsigned altExit)
{
  rxThrottle = (uint16_t)thr;
  rxRoll = roll10 / 10.0f;
  rxPitch = pitch10 / 10.0f;
  rxYaw = (float)yaw;
  rxFlightState = (uint8_t)fs;
  rxAltActive = flightStateActive(rxFlightState);
  rxAltExit = (uint8_t)altExit;
  rxAltitudeM = altCm / 100.0f;
  lastStatusMs = millis();
  statusSeen = true;
  ++validStatusCount;
  statusDiagnostic = String("Status hop le: ") + flightStateText(rxFlightState);

  // Dang bay ma STM32 tat ALT_HOLD:
  //  - LANDED: ha canh binh thuong, STM da/ dang ve idle -> giu mode 2,
  //    bam LEN/CAT CANH lai la bay tiep, khong can KICH HOAT LAI.
  //  - Ly do khac (baro, failsafe, cat canh that bai...): coi la loi -> DUNG.
  if (!stopped)
  {
    if (rxAltActive)
    {
      altWasActive = true;
    }
    else if (altWasActive)
    {
      altWasActive = false;
      webLostLanding = false;
      zeroCommands();
      if (rxAltExit == ALT_EXIT_LANDED)
      {
        Serial.println("STM32 da ha canh (ALT_EXIT_LANDED)");
      }
      else
      {
        // KHONG stopNow() ngay: neu STM con ga > 1000 thi no dang ha ga ve idle,
        // gui mode 0 luc nay se cat motor theo buoc. Cho STM tu ve 1000.
        static char reason[80];
        snprintf(reason, sizeof(reason), "STM32 thoat ALT_HOLD: %s (ma %u)",
                 altExitText(rxAltExit), (unsigned)rxAltExit);
        faultText = reason;
        faultStopPending = true;
        statusDiagnostic = faultText;
      }
    }
    // Kiem tra o MOI goi S, khong chi luc vua thoat ALT_HOLD.
    if (faultStopPending)
    {
      if (rxThrottle == MIN_THR)
        stopNow(faultText.c_str());
      else
        statusDiagnostic = faultText + " - dang ha ga";
    }
  }
  else
  {
    altWasActive = false;
  }
}

void onFrame(String frame)
{
  // Trong phien, BAT KY dong hoan chinh nao tu STM (dung hay hong) deu
  // nghia la STM da phat xong -> ket thuc phien som, khong doi het timeout.
  const uint32_t now = millis();
  const bool inPoll = (linkState == LinkState::WAIT_REPLY);
  if (inPoll)
    endPoll(now);

  if (frame.indexOf('*') < 0)
    return;
  if (!decodeFrame(frame))
  {
    ++radioRxErrors;
    ++invalidStatusCount;
    statusDiagnostic = "Sai checksum goi tra loi";
    return;
  }
  const char kind = frame.length() > 2 && frame[1] == ',' ? frame[0] : '?';
  if (kind != 'S' && kind != 'G' && kind != 'M')
    return;

  unsigned long seq = 0;
  int pos = 0;
  bool ok = false;
  const char *c = frame.c_str();
  const int len = (int)frame.length();

  // Gia tri tam, chi ap dung khi seq khop phien.
  unsigned thr = 0, fs = 0, altExit = 0;
  int roll10 = 0, pitch10 = 0, yaw = 0, altCm = 0;
  unsigned fix = 0, sats = 0;
  double lat = 0, lon = 0;
  long spd10 = 0, course = 0;
  unsigned m[4] = {0, 0, 0, 0};
  unsigned long rxT = 0, rxBad = 0, late = 0, uerr = 0, ovf = 0;

  if (kind == 'S')
  {
    ok = sscanf(c, "S,%lu,%u,%d,%d,%d,%u,%d,%u%n", &seq, &thr, &roll10, &pitch10,
                &yaw, &fs, &altCm, &altExit, &pos) == 8 &&
         pos == len && thr >= MIN_THR && thr <= MAX_THR && fs <= FS_MAX &&
         altExit <= ALT_EXIT_MAX && roll10 >= -1800 && roll10 <= 1800 &&
         pitch10 >= -900 && pitch10 <= 900 && yaw >= 0 && yaw < 360;
  }
  else if (kind == 'G')
  {
    ok = sscanf(c, "G,%lu,%u,%lf,%lf,%ld,%ld,%u%n", &seq, &fix, &lat, &lon, &spd10,
                &course, &sats, &pos) == 7 &&
         pos == len && fix <= 1U && isfinite(lat) && isfinite(lon) &&
         lat >= -90.0 && lat <= 90.0 && lon >= -180.0 && lon <= 180.0 &&
         spd10 >= 0 && course >= 0 && course < 360 && sats <= 99U;
  }
  else
  {
    ok = sscanf(c, "M,%lu,%u,%u,%u,%u,%lu,%lu,%lu,%lu,%lu%n", &seq, &m[0], &m[1],
                &m[2], &m[3], &rxT, &rxBad, &late, &uerr, &ovf, &pos) == 10 &&
         pos == len;
    for (int i = 0; i < 4 && ok; ++i)
      ok = m[i] >= MIN_THR && m[i] <= MAX_MOTOR_STATUS_US;
  }

  if (!ok)
  {
    ++invalidStatusCount;
    statusDiagnostic = "Goi tra loi sai so truong hoac ngoai gioi han";
    Serial.print("Reply invalid: ");
    Serial.println(frame);
    return;
  }
  // Tra loi phai dung T vua gui; goi tre/ngoai phien thi bo.
  if (!inPoll || seq != pendingSeq)
  {
    ++replyMismatchCount;
    Serial.printf("%c bo qua: seq=%lu pending=%lu inPoll=%u\n", kind,
                  seq, (unsigned long)pendingSeq, (unsigned)inPoll);
    return;
  }
  lastRttMs = now - pollSentMs;
  if (lastRttMs > maxRttMs)
    maxRttMs = lastRttMs;
  ++replyOkCount;

  if (kind == 'S')
  {
    applyStatusS(thr, roll10, pitch10, yaw, fs, altCm, altExit);
  }
  else if (kind == 'G')
  {
    // Khong fix -> 0 va KHONG duoc coi la vi tri that.
    rxGpsFix = (fix == 1U);
    rxGpsLat = rxGpsFix ? lat : 0.0;
    rxGpsLon = rxGpsFix ? lon : 0.0;
    rxGpsSpeedKmh = rxGpsFix ? spd10 / 10.0f : 0.0f;
    rxGpsCourseDeg = rxGpsFix ? (float)course : 0.0f;
    rxGpsSatellites = rxGpsFix ? sats : 0;
  }
  else
  {
    for (int i = 0; i < 4; ++i)
      rxMotors[i] = (uint16_t)m[i];
    diagSeen = true;
    diagStmRxT = rxT;
    diagStmRxBad = rxBad;
    diagStmLate = late;
    diagStmUartErr = uerr;
    diagStmRxOvf = ovf;
  }
}

void pollRadio()
{
  uint32_t now = millis();
  radioAuxReady(now);
  while (LoRa.available() > 0)
  {
    int data = LoRa.read();
    if (data < 0)
      break;
    ++radioRxByteCount;
    char c = (char)data;
    lastRxByteMs = millis();
    if (c == '\n')
    {
      if (!rxDiscard && rxLength > 0)
      {
        rxLine[rxLength] = '\0';
        lastRadioRx = String(rxLine, rxLength);
        lastRadioRxMs = millis();
        ++radioRxCount;
        Serial.print("RX < ");
        Serial.println(lastRadioRx);
        onFrame(lastRadioRx);
      }
      rxLength = 0;
      rxDiscard = false;
    }
    else if (c != '\r')
    {
      if (rxDiscard)
        continue;
      if (c != '\0' && rxLength < sizeof(rxLine) - 1)
      {
        rxLine[rxLength++] = c;
      }
      else
      {
        ++radioRxErrors;
        rxLength = 0;
        rxDiscard = true;
      }
    }
  }
  if ((rxLength > 0 || rxDiscard) && (uint32_t)(millis() - lastRxByteMs) > RX_PARTIAL_TIMEOUT_MS)
  {
    if (!rxDiscard)
      ++radioRxErrors;
    rxLength = 0;
    rxDiscard = true;
  }
}

void setupWebRoutes()
{
  web.on("/", HTTP_GET, []()
         { web.send_P(200, "text/html; charset=utf-8", INDEX_HTML); });

  web.on("/api/state", HTTP_GET, []()
         {
    lastWebMs = millis();
    const uint32_t now = millis();
    String json;
    json.reserve(1800);
    json = "{\"stopped\":" + String(stopped ? "true" : "false") + ",\"stopReason\":" + jsonString(stopReason) + ",\"link\":" + String(freshStatus() ? "true" : "false") + ",\"statusSeen\":" + String(statusSeen ? "true" : "false") + ",\"statusAgeMs\":" + (statusSeen ? String((uint32_t)(now - lastStatusMs)) : String("null")) + ",\"statusValidCount\":" + String(validStatusCount) + ",\"statusInvalidCount\":" + String(invalidStatusCount) + ",\"statusDiagnostic\":" + jsonString(statusDiagnostic);
    json += ",\"radio\":{\"ready\":" + String(radioReady(now) ? "true" : "false") + ",\"auxReady\":" + String(radioAuxReady(now) ? "true" : "false") + ",\"txCount\":" + String(radioTxCount) + ",\"rxCount\":" + String(radioRxCount) + ",\"rxErrors\":" + String(radioRxErrors) + ",\"txErrors\":" + String(radioTxErrors) + ",\"rttMs\":" + String(lastRttMs) + ",\"rttMaxMs\":" + String(maxRttMs) + ",\"replyOk\":" + String(replyOkCount) + ",\"replyTimeout\":" + String(replyTimeoutCount) + ",\"replyMismatch\":" + String(replyMismatchCount) + ",\"lastRx\":" + jsonString(lastRadioRx) + ",\"lastTx\":" + jsonString(lastRadioTx) + "}";
    if (statusSeen) {
      json += ",\"status\":{\"throttle\":" + String(rxThrottle) + ",\"roll\":" + String(rxRoll, 1) + ",\"pitch\":" + String(rxPitch, 1) + ",\"yaw\":" + String(rxYaw, 1) + ",\"altActive\":" + String(rxAltActive ? "true" : "false") + ",\"altExit\":" + String(rxAltExit) + ",\"altExitText\":" + jsonString(altExitText(rxAltExit)) + ",\"flightState\":" + String(rxFlightState) + ",\"flightStateText\":" + jsonString(flightStateText(rxFlightState)) + ",\"altitudeM\":" + String(rxAltitudeM, 2) + ",\"motors\":[";
      for (int i = 0; i < 4; i++) {
        if (i) json += ',';
        json += String(rxMotors[i]);
      }
      json += "],\"gpsFix\":" + String(rxGpsFix ? "true" : "false") + ",\"gpsLat\":" + String(rxGpsLat, 6) + ",\"gpsLon\":" + String(rxGpsLon, 6) + ",\"gpsSpeedKmh\":" + String(rxGpsSpeedKmh, 1) + ",\"gpsCourseDeg\":" + String(rxGpsCourseDeg, 1) + ",\"gpsSatellites\":" + String(rxGpsSatellites) + "}";
    }
    if (diagSeen) {
      json += ",\"stmDiag\":{\"rxT\":" + String(diagStmRxT) + ",\"rxBad\":" + String(diagStmRxBad) + ",\"lateDrop\":" + String(diagStmLate) + ",\"uartErr\":" + String(diagStmUartErr) + ",\"rxOvf\":" + String(diagStmRxOvf) + "}";
    }
    json += ",\"climb\":" + String(climbCommand) + ",\"rollCommand\":" + String(rollCommand) + ",\"pitchCommand\":" + String(pitchCommand) + ",\"yawRateCommand\":" + String(yawRateCommand) + "}";
    web.send(200, "application/json", json); });

  // Mot endpoint duy nhat: climb/roll/pitch/yaw cung luc. Tha cat = gui 0 = giu do cao.
  web.on("/api/ctrl", HTTP_POST, []()
         {
    int16_t c = 0, r = 0, p = 0, y = 0;
    if (!parseSigned(web.arg("climb"), -100, 100, &c) || !parseSigned(web.arg("roll"), -MAX_ROLL_PITCH_DEG, MAX_ROLL_PITCH_DEG, &r) || !parseSigned(web.arg("pitch"), -MAX_ROLL_PITCH_DEG, MAX_ROLL_PITCH_DEG, &p) || !parseSigned(web.arg("yaw"), -MAX_YAW_DPS, MAX_YAW_DPS, &y)) {
      respondError("Gia tri ngoai gioi han");
      return;
    }
    lastWebMs = millis();
    if (stopped) {
      respondError("Da DUNG. Bam KICH HOAT LAI", 409);
      return;
    }
    if (!freshStatus()) {
      if (c || r || p || y) {
        respondError("Chua co status STM32 moi", 409);
        return;
      }
    } else if (!rxAltActive) {
      // Tren mat dat: chi cho LEN (cat canh). Khong ha, khong nghieng.
      if (c < 0) c = 0;
      r = p = y = 0;
    }
    const bool changed = (c != climbCommand || r != rollCommand || p != pitchCommand || y != yawRateCommand);
    climbCommand = c;
    rollCommand = r;
    pitchCommand = p;
    yawRateCommand = y;
    lastCmdMs = millis();
    webLostLanding = false;  // nguoi lai da quay lai, nhuong quyen dieu khien
    if (changed) forceTxSoon();
    respondOk(); });

  web.on("/api/stop", HTTP_POST, []()
         {
    lastWebMs = millis();
    stopNow("Web emergency STOP");
    respondOk(); });

  // Chi kich hoat lai khi STM32 da xac nhan dung: ga THAT = 1000 va ALT_ACTIVE=0.
  web.on("/api/resume", HTTP_POST, []()
         {
    lastWebMs = millis();
    if (!stopped) {
      respondOk();   
      return;
    }
    if (!freshStatus() || rxThrottle != MIN_THR || rxAltActive) {
      respondError("Cho STM32 xac nhan da dung (thr=1000, ALT_ACTIVE=0)", 409);
      return;
    }
    stopped = false;
    stopReason = "";
    altWasActive = false;
    webLostLanding = false;
    faultStopPending = false;
    climbCommand = rollCommand = pitchCommand = yawRateCommand = 0;
    forceTxSoon();
    respondOk(); });

  web.onNotFound([]()
                 { web.send(404, "text/plain", "Not found"); });
}

void maintainWiFi()
{
  static bool wasConnected = false;
  static uint32_t lastRetry = 0;
  const uint32_t now = millis();
  const bool connected = WiFi.status() == WL_CONNECTED;
  if (connected && !wasConnected)
  {
    Serial.print("WEB: http://");
    Serial.println(WiFi.localIP());
  }
  else if (!connected && wasConnected)
  {
    zeroCommands(); // giu do cao; WEB_LOST_STOP_MS se xu ly neu mat lau
  }
  wasConnected = connected;
  if (!connected && (uint32_t)(now - lastRetry) >= WIFI_RETRY_MS)
  {
    lastRetry = now;
    WiFi.reconnect();
  }
}

void setup()
{
  Serial.begin(115200);
  delay(350);
  pinMode(E220_M0, OUTPUT);
  pinMode(E220_M1, OUTPUT);
  if (E220_AUX >= 0)
    pinMode(E220_AUX, INPUT_PULLUP);
  digitalWrite(E220_M0, LOW);
  digitalWrite(E220_M1, LOW);
  LoRa.setRxBufferSize(512);
  LoRa.setTxBufferSize(256);
  LoRa.begin(UART_BAUD, SERIAL_8N1, E220_RX, E220_TX);
  radioStarted = static_cast<bool>(LoRa);
  if (!radioStarted)
  {
    ++radioTxErrors;
    Serial.println("E220 init fail");
  }
  setupWebRoutes();
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  web.begin();
  pollDoneMs = millis();
  lastWebMs = millis();
  Serial.println("Web drone: luon mode 2 (ALT_HOLD). http://<ESP32 IP>/");
}

void loop()
{
  maintainWiFi();
  web.handleClient();
  pollRadio();
  processRadioTx();
  static uint32_t lastDebug = 0;
  const uint32_t now = millis();
  if ((uint32_t)(now - lastDebug) >= 1000)
  {
    lastDebug = now;
    // Tach mat goi theo chieu: TX (ESP gui) vs stmRxT (STM nhan T hop le)
    // -> mat chieu xuong; stmRxT vs OK -> mat chieu len.
    Serial.printf("TX=%lu OK=%lu TO=%lu MIS=%lu RTT=%lu RTTmax=%lu RXERR=%lu RXB=%lu "
                  "stmRxT=%lu stmBad=%lu stmLate=%lu stmUart=%lu STOP=%u CL=%d FS=%u H=%.2f\n",
                  (unsigned long)radioTxCount, (unsigned long)replyOkCount,
                  (unsigned long)replyTimeoutCount, (unsigned long)replyMismatchCount,
                  (unsigned long)lastRttMs, (unsigned long)maxRttMs,
                  (unsigned long)radioRxErrors, (unsigned long)radioRxByteCount,
                  diagStmRxT, diagStmRxBad, diagStmLate, diagStmUartErr,
                  (unsigned)stopped, (int)climbCommand, (unsigned)rxFlightState, rxAltitudeM);
  }
  delay(1);
}