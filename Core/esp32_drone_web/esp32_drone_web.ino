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

// ---- Master-slave timing (9600 baud / 2.4k, T ~30 byte, S ~100 byte) ----
// Timeout PHAI lon hon RTT xau nhat (xem "RTT=" tren Serial), neu khong
// ESP se phat chong len luc STM dang tra loi.
// Rang buoc voi STM32 (drone_link.h / main.c):
//   REPLY_TIMEOUT_MS + POLL_GUARD_MS + ~150 ms truyen T < DRONE_LINK_CLIMB_TIMEOUT_MS (2200)
//   DRONE_LINK_CLIMB_TIMEOUT_MS < LINK_LOST_MS (3000) -> mat 1 goi S khong kich failsafe.
// Doi so nay thi phai doi ca 2 hang so ben STM32.
constexpr uint32_t REPLY_TIMEOUT_MS = 1800;
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
  ALT_EXIT_MAX = ALT_EXIT_IMU
};

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
uint32_t pollSentMs = 0, pollDoneMs = 0, lastRttMs = 0;
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

// ---- Goi S tu STM32 (18 truong, co GPS + ly do thoat ALT_HOLD) ----
// S,seq,thr,r,p,y,m1,m2,m3,m4,altActive,altM,fix,lat,lon,speed,course,sats,altExit
// thr = ga that dang ra mixer.
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
    if (frame.startsWith("S,"))
    {
      ++invalidStatusCount;
      statusDiagnostic = "Sai checksum status S";
    }
    return;
  }
  if (!frame.startsWith("S,"))
    return;

  unsigned long seq = 0;
  unsigned thr = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0, active = 0, fix = 0, sats = 0, altExit = 0;
  float r = 0, p = 0, y = 0, altitude = 0, speedKmh = 0, courseDeg = 0;
  double latitude = 0, longitude = 0;
  int pos = 0;
  const int fields = sscanf(frame.c_str(),
                            "S,%lu,%u,%f,%f,%f,%u,%u,%u,%u,%u,%f,%u,%lf,%lf,%f,%f,%u,%u%n",
                            &seq, &thr, &r, &p, &y, &m1, &m2, &m3, &m4,
                            &active, &altitude, &fix, &latitude, &longitude,
                            &speedKmh, &courseDeg, &sats, &altExit, &pos);

  const bool shapeOk = (fields == 18 && pos == (int)frame.length() && altExit <= ALT_EXIT_MAX);
  const bool gpsOk = fix <= 1U && isfinite(latitude) && isfinite(longitude) && latitude >= -90.0 && latitude <= 90.0 && longitude >= -180.0 && longitude <= 180.0 && isfinite(speedKmh) && speedKmh >= 0.0f && isfinite(courseDeg) && courseDeg >= 0.0f && courseDeg <= 360.0f && sats <= 99U;
  if (shapeOk && gpsOk && active <= 1U && isfinite(altitude) && thr >= MIN_THR && thr <= MAX_THR && isfinite(r) && isfinite(p) && isfinite(y) && m1 >= MIN_THR && m1 <= MAX_MOTOR_STATUS_US && m2 >= MIN_THR && m2 <= MAX_MOTOR_STATUS_US && m3 >= MIN_THR && m3 <= MAX_MOTOR_STATUS_US && m4 >= MIN_THR && m4 <= MAX_MOTOR_STATUS_US)
  {
    // S phai tra loi dung T vua gui; goi tre/ngoai phien thi bo.
    if (!inPoll || seq != pendingSeq)
    {
      ++replyMismatchCount;
      Serial.printf("S bo qua: seq=%lu pending=%lu inPoll=%u\n",
                    seq, (unsigned long)pendingSeq, (unsigned)inPoll);
      return;
    }
    lastRttMs = now - pollSentMs;
    ++replyOkCount;

    rxThrottle = (uint16_t)thr;
    rxRoll = r;
    rxPitch = p;
    rxYaw = y;
    rxAltActive = active != 0;
    rxAltExit = (uint8_t)altExit;
    rxAltitudeM = altitude;
    rxMotors[0] = m1;
    rxMotors[1] = m2;
    rxMotors[2] = m3;
    rxMotors[3] = m4;
    rxGpsFix = (fix == 1U);
    rxGpsLat = rxGpsFix ? latitude : 0.0;
    rxGpsLon = rxGpsFix ? longitude : 0.0;
    rxGpsSpeedKmh = rxGpsFix ? speedKmh : 0.0f;
    rxGpsCourseDeg = rxGpsFix ? courseDeg : 0.0f;
    rxGpsSatellites = rxGpsFix ? sats : 0;
    lastStatusMs = millis();
    statusSeen = true;
    ++validStatusCount;
    statusDiagnostic = "Status S + GPS hop le";

    // Dang bay ma STM32 tat ALT_HOLD:
    //  - LANDED: ha canh binh thuong, STM da disarm (motor 1000) -> giu mode 2,
    //    bam LEN/CAT CANH lai la bay tiep, khong can KICH HOAT LAI.
    //  - Ly do khac (baro, failsafe...): coi la loi -> DUNG.
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
          // KHONG stopNow() ngay: neu STM con ga > 1000 thi no dang ha khan cap,
          // gui mode 0 luc nay se cat motor giua troi. Cho STM tu ve 1000.
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
          statusDiagnostic = faultText + " - dang ha canh khan cap";
      }
    }
    else
    {
      altWasActive = false;
    }
  }
  else
  {
    ++invalidStatusCount;
    statusDiagnostic = "Status S sai so truong hoac ngoai gioi han";
    Serial.print("S invalid: ");
    Serial.println(frame);
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
    json += ",\"radio\":{\"ready\":" + String(radioReady(now) ? "true" : "false") + ",\"auxReady\":" + String(radioAuxReady(now) ? "true" : "false") + ",\"txCount\":" + String(radioTxCount) + ",\"rxCount\":" + String(radioRxCount) + ",\"rxErrors\":" + String(radioRxErrors) + ",\"txErrors\":" + String(radioTxErrors) + ",\"rttMs\":" + String(lastRttMs) + ",\"replyOk\":" + String(replyOkCount) + ",\"replyTimeout\":" + String(replyTimeoutCount) + ",\"replyMismatch\":" + String(replyMismatchCount) + ",\"lastRx\":" + jsonString(lastRadioRx) + ",\"lastTx\":" + jsonString(lastRadioTx) + "}";
    if (statusSeen) {
      json += ",\"status\":{\"throttle\":" + String(rxThrottle) + ",\"roll\":" + String(rxRoll, 1) + ",\"pitch\":" + String(rxPitch, 1) + ",\"yaw\":" + String(rxYaw, 1) + ",\"altActive\":" + String(rxAltActive ? "true" : "false") + ",\"altExit\":" + String(rxAltExit) + ",\"altExitText\":" + jsonString(altExitText(rxAltExit)) + ",\"altitudeM\":" + String(rxAltitudeM, 2) + ",\"motors\":[";
      for (int i = 0; i < 4; i++) {
        if (i) json += ',';
        json += String(rxMotors[i]);
      }
      json += "],\"gpsFix\":" + String(rxGpsFix ? "true" : "false") + ",\"gpsLat\":" + String(rxGpsLat, 6) + ",\"gpsLon\":" + String(rxGpsLon, 6) + ",\"gpsSpeedKmh\":" + String(rxGpsSpeedKmh, 1) + ",\"gpsCourseDeg\":" + String(rxGpsCourseDeg, 1) + ",\"gpsSatellites\":" + String(rxGpsSatellites) + "}";
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
    Serial.printf("TX=%lu OK=%lu TO=%lu MIS=%lu RTT=%lu STOP=%u CL=%d ALT=%u H=%.2f\n",
                  (unsigned long)radioTxCount, (unsigned long)replyOkCount,
                  (unsigned long)replyTimeoutCount, (unsigned long)replyMismatchCount,
                  (unsigned long)lastRttMs, (unsigned)stopped, (int)climbCommand,
                  (unsigned)rxAltActive, rxAltitudeM);
  }
  delay(1);
}