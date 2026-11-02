#include <Arduino.h>
#include <HardwareSerial.h>
#include <Bluepad32.h>
#include <WiFi.h>
#include <WebServer.h>
#include <math.h>
#include "index_html.h"

constexpr char WIFI_SSID[] = "DESKTOP-7F2FABB 9674";
constexpr char WIFI_PASS[] = "khanhkhanh";
constexpr uint32_t WIFI_RETRY_MS = 10000;
#if defined(CONFIG_IDF_TARGET_ESP32S3)
constexpr int E220_RX = 18;
constexpr int E220_TX = 17;
constexpr int E220_M0 = 4;
constexpr int E220_M1 = 5;
constexpr int E220_AUX = 6;
#elif defined(CONFIG_IDF_TARGET_ESP32)
constexpr int E220_RX = 16;
constexpr int E220_TX = 17;
/* Day cu: M0=25 M1=26 AUX=27.
 * Neu da DAU LAI DAY theo file 154138: M0=26 M1=27 AUX=25,
 * doi gia tri E220_PINMAP_SWAPPED thanh 1.
 */
#define E220_PINMAP_SWAPPED 0
#if E220_PINMAP_SWAPPED
constexpr int E220_M0 = 26;
constexpr int E220_M1 = 27;
constexpr int E220_AUX = 25;
#else
constexpr int E220_M0 = 25;
constexpr int E220_M1 = 26;
constexpr int E220_AUX = 27;
#endif
#else
#error "Select ESP32 Dev Module or ESP32S3 Dev Module."
#endif
constexpr uint32_t UART_BAUD = 9600;
constexpr uint16_t MIN_THR = 1000;
constexpr uint16_t MAX_THR = 1700;
constexpr uint16_t MAX_MOTOR_STATUS_US = 2000;

constexpr uint32_t THROTTLE_PERIOD_MS = 1500;     // Baseline da su dung truoc ALT_HOLD
constexpr uint32_t ALT_TX_PERIOD_MS = 650;        // Thu nghiem ALT, chi khi nhan duoc status S
constexpr uint32_t ALT_STATUS_TIMEOUT_MS = 1200;  // Het han doi S, co the gui lai
constexpr uint32_t PID_HEARTBEAT_MS = 2500;
constexpr uint32_t CLIENT_TIMEOUT_MS = 3000;
constexpr uint32_t STATUS_VALID_MS = 6500;
constexpr uint32_t MIN_RADIO_GAP_MS = 900;      // Khoang cach gui MANUAL cu
constexpr uint32_t ALT_MIN_RADIO_GAP_MS = 450;  // Thu nghiem, khong su dung bay tu do
constexpr uint32_t AUX_SETTLE_MS = 3;
constexpr uint32_t RX_PARTIAL_TIMEOUT_MS = 1200;
constexpr size_t MAX_RADIO_PACKET_BYTES = 200;
constexpr uint32_t ACK_TIMEOUT_MS = 2200;
constexpr uint8_t MAX_ATTEMPTS = 4;
// PS4 left stick: up negative, down positive, resting ~+4.
constexpr int PS4_DEADZONE = 40;
constexpr int16_t MAX_CLIMB_CM_S = 30;  // Trial only: +/- 0.30 m/s
constexpr uint32_t PS4_REPORT_TIMEOUT_MS = 400;
// Bluetooth gets priority. Start web Wi-Fi only after PS4 has been linked.
constexpr uint32_t PS4_WIFI_START_DELAY_MS = 2000;
// Change to 1 to debug PS4 + E220 without any Wi-Fi radio contention.
#define PS4_DIAGNOSTIC_DISABLE_WIFI 1


// The altitude controller, hover PWM and ground detection belong on STM32.
// T,seq,1000,1,climb_cm_s,home  (ALT_HOLD V2; NOT old STM32 compatible)
ControllerPtr ps4 = nullptr;
uint32_t lastPS4ReportMs = 0;
uint32_t ps4ConnectedSinceMs = 0;
bool wifiStarted = false;
int16_t lastLY = 4;
bool lastL3Down = false;
bool homeRequested = false;
bool commandDirty = true;

WebServer web(80);
HardwareSerial LoRa(2);

struct PidGains {
  float kp, ki, kd;
};

PidGains pids[5] = {
  { 7.2f, 0.0f, 0.0f },
  { 8.0f, 0.0f, 0.0f },
  { 0.8f, 0.2f, 0.0f },
  { 0.8f, 0.2f, 0.0f },
  { 0.3f, 0.0f, 0.0f }
};

uint16_t throttle = MIN_THR;  // Retained legacy field; NOT used as a PWM command in ALT V2.
/* Altitude-hold is the only flight-control mode; STM32 must implement V2. */
bool altHoldMode = true;
int16_t climbCommand = 0;
uint32_t lastClimbUpdateMs = 0;
uint32_t lastWebMs = 0;
uint32_t lastTxMs = 0;
uint32_t lastThrottleTxMs = 0;
uint32_t nextSeq = 1;
uint32_t lastThrottleSeq = 0;
bool throttleReplyPending = false;
uint32_t lastThrottleSendMs = 0;

bool statusSeen = false;
uint32_t lastStatusMs = 0;
uint32_t validStatusCount = 0;
uint32_t invalidStatusCount = 0;
String statusDiagnostic = "Chua nhan goi status S hop le";
uint16_t rxThrottle = MIN_THR;
float rxRoll = 0, rxPitch = 0, rxYaw = 0;
uint16_t rxMotors[4] = { 1000, 1000, 1000, 1000 };

enum OpType { OP_NONE,
              OP_APPLY,
              OP_READ };
OpType operation = OP_NONE;
PidGains pendingPids[5];
uint8_t opIndex = 0;
uint8_t attempts = 0;
uint32_t waitingSeq = 0;
uint32_t lastOpMs = 0;
bool waiting = false;
String opText = "Không có yêu cầu PID";

char rxLine[176];
size_t rxLength = 0;
bool rxDiscard = false;
uint32_t lastRxByteMs = 0;
bool radioStarted = false;
bool auxWasHigh = false;
uint32_t auxHighSinceMs = 0;
uint32_t radioTxCount = 0;
uint32_t radioRxCount = 0;
uint32_t radioRxByteCount = 0;
uint32_t radioRxErrors = 0;
uint32_t radioTxErrors = 0;
uint32_t lastRadioRxMs = 0;
String lastRadioRx;
String lastRadioTx;

String jsonString(const String &value) {
  String escaped;
  escaped.reserve(value.length() + 2);
  escaped += '"';
  for (size_t i = 0; i < value.length(); ++i) {
    const uint8_t c = static_cast<uint8_t>(value[i]);
    if (c == '"' || c == '\\') {
      escaped += '\\';
      escaped += static_cast<char>(c);
    } else if (c >= 0x80) {

      const size_t count = c >= 0xC2 && c <= 0xDF ? 2 : c >= 0xE0 && c <= 0xEF ? 3
                                                      : c >= 0xF0 && c <= 0xF4 ? 4
                                                                               : 0;
      bool valid = count != 0 && i + count <= value.length();
      for (size_t j = 1; valid && j < count; ++j) {
        const uint8_t next = static_cast<uint8_t>(value[i + j]);
        valid = next >= 0x80 && next <= 0xBF;
        if (j == 1)
          valid = valid && !(c == 0xE0 && next < 0xA0) && !(c == 0xED && next > 0x9F) && !(c == 0xF0 && next < 0x90) && !(c == 0xF4 && next > 0x8F);
      }
      if (valid) {
        for (size_t j = 0; j < count; ++j)
          escaped += value[i + j];
        i += count - 1;
      } else {
        char hex[7];
        snprintf(hex, sizeof(hex), "\\u%04X", static_cast<unsigned>(c));
        escaped += hex;
      }
    } else if (c < 0x20 || c == 0x7F) {

      char hex[7];
      snprintf(hex, sizeof(hex), "\\u%04X", static_cast<unsigned>(c));
      escaped += hex;
    } else {
      escaped += static_cast<char>(c);
    }
  }
  escaped += '"';
  return escaped;
}

uint8_t xorChecksum(const String &s) {
  uint8_t v = 0;
  for (size_t i = 0; i < s.length(); i++)
    v ^= uint8_t(s[i]);
  return v;
}

String frameOf(const String &payload) {
  char hex[5];
  snprintf(hex, sizeof(hex), "*%02X\n", xorChecksum(payload));
  return payload + hex;
}

bool decodeFrame(String &raw) {
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

bool radioAuxReady(uint32_t now) {
  if (E220_AUX < 0)
    return true;
  if (digitalRead(E220_AUX) == LOW) {
    auxWasHigh = false;
    return false;
  }
  if (!auxWasHigh) {
    auxWasHigh = true;
    auxHighSinceMs = now;
  }
  return (uint32_t)(now - auxHighSinceMs) >= AUX_SETTLE_MS;
}

bool radioReady(uint32_t now) {
  const uint32_t gap = altHoldMode ? ALT_MIN_RADIO_GAP_MS : MIN_RADIO_GAP_MS;
  return radioStarted && radioAuxReady(now) && (uint32_t)(now - lastTxMs) >= gap;
}

bool sendRadioBytes(const String &packet, const String &description) {
  uint32_t now = millis();
  if (!radioReady(now))
    return false;
  if (packet.length() == 0 || packet.length() > MAX_RADIO_PACKET_BYTES) {
    ++radioTxErrors;
    return false;
  }

  const size_t written = LoRa.write(
    reinterpret_cast<const uint8_t *>(packet.c_str()), packet.length());

  LoRa.flush(true);
  lastTxMs = millis();
  if (written != packet.length()) {
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

bool sendRadio(const String &payload) {
  return sendRadioBytes(frameOf(payload), payload);
}

/* ALT V2 control frame: T,seq,1000,1,climb_cm_s,home
 * The fixed 1000 is a legacy placeholder, NOT a motor PWM setpoint.
 * L3 = home=1 latched until the pilot moves LY again.
 * Existing drone_link.c rejects this frame; STM32 receiver must be upgraded.
 */
String makeThrottlePayload(uint32_t seq) {
  return "T," + String(seq) + ",1000,1," + String(climbCommand) + "," + String(homeRequested ? 1 : 0);
}

bool sendThrottleFrame() {
  const uint32_t seq = nextSeq;
  if (!sendRadio(makeThrottlePayload(seq))) return false;
  ++nextSeq;
  lastThrottleSeq = seq;
  throttleReplyPending = true;
  lastThrottleSendMs = millis();
  lastThrottleTxMs = lastThrottleSendMs;
  return true;
}

bool freshStatus() {
  return statusSeen && (uint32_t)(millis() - lastStatusMs) <= STATUS_VALID_MS;
}

bool parseGain(const String &text, float &v) {
  if (!text.length())
    return false;
  char *end = nullptr;
  v = strtof(text.c_str(), &end);
  return end != text.c_str() && *end == 0 && isfinite(v) && v >= 0 && v <= 100;
}

void respondOk() {
  web.send(200, "application/json", "{\"ok\":true}");
}

void respondError(const String &reason, int status = 400) {
  web.send(status, "application/json", "{\"ok\":false,\"error\":" + jsonString(reason) + "}");
}

void onFrame(String frame) {
  if (frame.indexOf('*') < 0) return;
  if (!decodeFrame(frame)) {
    ++radioRxErrors;
    if (frame.startsWith("S,")) {
      ++invalidStatusCount;
      statusDiagnostic = "Sai checksum status S";
    }
    return;
  }

  const char kind = frame[0];
  unsigned long seq = 0;
  unsigned id = 0;
  int pos = 0;

  if ((kind == 'A' || kind == 'N') && operation == OP_APPLY && waiting && sscanf(frame.c_str(), "%*c,%lu,%u%n", &seq, &id, &pos) == 2 && pos == (int)frame.length() && seq == waitingSeq && id == opIndex) {
    waiting = false;
    if (kind == 'N') {
      operation = OP_NONE;
      lastThrottleTxMs = millis() - THROTTLE_PERIOD_MS;
      opText = "STM32 từ chối PID " + String(id);
    } else {
      pids[id] = pendingPids[id];
      ++opIndex;
      attempts = 0;
      if (opIndex == 5) {
        operation = OP_NONE;
        lastThrottleTxMs = millis() - THROTTLE_PERIOD_MS;
        opText = "Đã gửi PID: 5/5 ACK";
      }
    }
  } else if (kind == 'R' && operation == OP_READ && waiting) {
    float kp = 0, ki = 0, kd = 0;
    pos = 0;
    if (sscanf(frame.c_str(), "R,%lu,%u,%f,%f,%f%n", &seq, &id, &kp, &ki, &kd, &pos) == 5 && pos == (int)frame.length() && seq == waitingSeq && id == opIndex && id < 5 && isfinite(kp) && isfinite(ki) && isfinite(kd) && kp >= 0 && kp <= 100 && ki >= 0 && ki <= 100 && kd >= 0 && kd <= 100) {
      pids[id] = { kp, ki, kd };
      waiting = false;
      ++opIndex;
      attempts = 0;
      if (opIndex == 5) {
        operation = OP_NONE;
        lastThrottleTxMs = millis() - THROTTLE_PERIOD_MS;
        opText = "Đã đọc PID từ drone: 5/5";
      }
    }
  } else if (kind == 'S') {

    unsigned thr = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0;
    float r = 0, p = 0, y = 0;
    pos = 0;
    if (sscanf(frame.c_str(), "S,%lu,%u,%f,%f,%f,%u,%u,%u,%u%n",
               &seq, &thr, &r, &p, &y, &m1, &m2, &m3, &m4, &pos)
          == 9
        && pos == (int)frame.length() && thr >= MIN_THR && thr <= MAX_THR && isfinite(r) && isfinite(p) && isfinite(y) && m1 >= MIN_THR && m1 <= MAX_MOTOR_STATUS_US && m2 >= MIN_THR && m2 <= MAX_MOTOR_STATUS_US && m3 >= MIN_THR && m3 <= MAX_MOTOR_STATUS_US && m4 >= MIN_THR && m4 <= MAX_MOTOR_STATUS_US) {
      rxThrottle = (uint16_t)thr;
      rxRoll = r;
      rxPitch = p;
      rxYaw = y;
      rxMotors[0] = m1;
      rxMotors[1] = m2;
      rxMotors[2] = m3;
      rxMotors[3] = m4;
      lastStatusMs = millis();
      if (throttleReplyPending && seq == lastThrottleSeq)
        throttleReplyPending = false;
      statusSeen = true;
      ++validStatusCount;
      statusDiagnostic = "Status S hợp lệ";
    } else {
      ++invalidStatusCount;
      statusDiagnostic = "Status S sai số trường hoặc ngoài giới hạn";
      Serial.print("S invalid: ");
      Serial.println(frame);
    }
  }
}

void pollRadio() {
  uint32_t now = millis();
  radioAuxReady(now);
  while (LoRa.available() > 0) {
    int data = LoRa.read();

    if (data < 0)
      break;

    ++radioRxByteCount;
    char c = (char)data;
    lastRxByteMs = millis();

    if (c == '\n') {
      if (!rxDiscard && rxLength > 0) {
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
    } else if (c != '\r') {
      if (rxDiscard)
        continue;
      if (c != '\0' && rxLength < sizeof(rxLine) - 1) {
        rxLine[rxLength++] = c;
      } else {
        ++radioRxErrors;
        rxLength = 0;
        rxDiscard = true;
      }
    }
  }

  if ((rxLength > 0 || rxDiscard) && (uint32_t)(millis() - lastRxByteMs) > RX_PARTIAL_TIMEOUT_MS) {
    if (!rxDiscard)
      ++radioRxErrors;
    rxLength = 0;

    rxDiscard = true;
  }
}

void startOperation(OpType type) {
  operation = type;
  opIndex = 0;
  attempts = 0;
  waiting = false;
  opText = type == OP_READ ? "Đang đọc PID: 0/5" : "Đang gửi PID: 0/5";
}

// -- Bluetooth PS4 -----------------------------------------------------------
static void requestControlTx() {
  commandDirty = true;
  lastThrottleTxMs = millis() - ALT_TX_PERIOD_MS;
}

static void onConnectedController(ControllerPtr ctl) {
  if (ps4 == nullptr && ctl && ctl->isGamepad()) {
    ps4 = ctl;
    lastPS4ReportMs = millis();
    ps4ConnectedSinceMs = lastPS4ReportMs;
    lastL3Down = false;
    lastLY = 4;
    climbCommand = 0;
    // Keep any existing L3 landing request across reconnection.
    Serial.printf("PS4 CONNECTED: %s\n", ctl->getModelName().c_str());
    requestControlTx();
  }
}

static void onDisconnectedController(ControllerPtr ctl) {
  if (ps4 == ctl) {
    ps4 = nullptr;
    ps4ConnectedSinceMs = 0;
    lastL3Down = false;
    lastLY = 4;
    climbCommand = 0;  // Missing controller => release to HOLD; not direct PWM=1000.
    Serial.println("PS4 DISCONNECTED: request hold current altitude");
    requestControlTx();
  }
}

static int16_t convertLYToClimbCmS(int ly) {
  ly = constrain(ly, -512, 512);
  int a = abs(ly);
  if (a <= PS4_DEADZONE) return 0;
  // Scale out the deadzone to avoid a jump at the center.
  int rate = (a - PS4_DEADZONE) * MAX_CLIMB_CM_S / (512 - PS4_DEADZONE);
  return (int16_t)(ly < 0 ? rate : -rate);
}

static void pollPS4() {
  BP32.update();
  const uint32_t now = millis();
  if (ps4 && ps4->isConnected() && ps4->isGamepad()) {
    if (ps4->hasData()) {
      lastPS4ReportMs = now;
      lastLY = ps4->axisY();
      bool l3 = ps4->thumbL();
      if (l3 && !lastL3Down) {
        homeRequested = true;  // Return to relative ground altitude 0m.
        if (climbCommand != 0) climbCommand = 0;
        requestControlTx();
        Serial.println("PS4 L3: return to altitude=0 (NOT motor cutoff)");
      }
      lastL3Down = l3;

      const int16_t cmd = convertLYToClimbCmS(lastLY);
      if (cmd != 0 && !l3 && homeRequested) {
        homeRequested = false;  // Any new stick movement cancels return-home.
        requestControlTx();
      }
      const int16_t selected = homeRequested ? 0 : cmd;
      if (selected != climbCommand) {
        climbCommand = selected;
        requestControlTx();
      }
      lastClimbUpdateMs = now;
    }
    if ((uint32_t)(now - lastPS4ReportMs) > PS4_REPORT_TIMEOUT_MS && climbCommand != 0) {
      climbCommand = 0;  // Stale BT data => stop moving, keep holding.
      requestControlTx();
    }
  } else {
    if (climbCommand != 0) {
      climbCommand = 0;
      requestControlTx();
    }
  }
}

void processRadioTx() {
  uint32_t now = millis();
  // Never derive altitude commands from webpage inactivity / old PWM.
  // Missing BT data is handled by pollPS4() and independently by the STM32 watchdog.
  // Missing RF ACK is a telemetry fault; it does not justify an abrupt motor cutoff.

  if (!radioReady(now)) return;

  if (operation != OP_NONE) {
    if (waiting) {
      if ((uint32_t)(now - lastOpMs) < ACK_TIMEOUT_MS) return;
      waiting = false;
      if (attempts >= MAX_ATTEMPTS) {
        opText = "Lỗi: PID " + String(opIndex) + " không phản hồi sau 4 lần";
        operation = OP_NONE;
        lastThrottleTxMs = millis() - THROTTLE_PERIOD_MS;
        return;
      }
    }

    if ((uint32_t)(now - lastThrottleTxMs) >= PID_HEARTBEAT_MS) {
      (void)sendThrottleFrame();
      return;
    }
    if (attempts == 0) waitingSeq = nextSeq++;
    String payload;
    if (operation == OP_APPLY) {
      const PidGains &p = pendingPids[opIndex];
      payload = "P," + String(waitingSeq) + "," + String(opIndex) + "," + String(p.kp, 4) + "," + String(p.ki, 4) + "," + String(p.kd, 4);
    } else {
      payload = "G," + String(waitingSeq) + "," + String(opIndex);
    }
    if (sendRadio(payload)) {
      waiting = true;
      ++attempts;
      lastOpMs = millis();
      opText = String(operation == OP_APPLY ? "Đang gửi PID " : "Đang đọc PID ") + String(opIndex + 1) + "/5, lần " + String(attempts);
    }
    return;
  }

  /* Khi ALT_HOLD: khong phat goi T moi ngay khi goi truoc chua co S,
   * de tranh 2 bo E220 tranh nhau tren kenh vo tuyen.
   * Neu mat S, thu lai sau timeout; khong bao gio giu lenh climb vo thoi han.
   */
  if (!commandDirty && throttleReplyPending && (uint32_t)(now - lastThrottleSendMs) < ALT_STATUS_TIMEOUT_MS)
    return;

  if (commandDirty || (uint32_t)(now - lastThrottleTxMs) >= ALT_TX_PERIOD_MS) {
    if (sendThrottleFrame()) commandDirty = false;
  }
}

void setupWebRoutes() {

  web.on("/", HTTP_GET, []() {
    web.send_P(200, "text/html; charset=utf-8", INDEX_HTML);
  });

  web.on("/api/state", HTTP_GET, []() {
    lastWebMs = millis();
    String json;
    json.reserve(2200);
    json = "{\"throttle\":" + String(throttle) + ",\"link\":" + String(freshStatus() ? "true" : "false") + ",\"operation\":" + jsonString(opText) + ",\"pids\":[";
    for (int i = 0; i < 5; i++) {
      if (i) json += ',';
      json += "{\"kp\":" + String(pids[i].kp, 4) + ",\"ki\":" + String(pids[i].ki, 4) + ",\"kd\":" + String(pids[i].kd, 4) + "}";
    }
    json += "],\"pidBusy\":" + String(operation != OP_NONE ? "true" : "false");
    const uint32_t now = millis();
    json += ",\"statusSeen\":" + String(statusSeen ? "true" : "false");
    json += ",\"statusAgeMs\":" + (statusSeen ? String((uint32_t)(now - lastStatusMs)) : String("null"));
    json += ",\"statusValidCount\":" + String(validStatusCount);
    json += ",\"statusInvalidCount\":" + String(invalidStatusCount);
    json += ",\"statusDiagnostic\":" + jsonString(statusDiagnostic);
    json += ",\"radio\":{\"ready\":" + String(radioReady(now) ? "true" : "false") + ",\"auxConnected\":" + String(E220_AUX >= 0 ? "true" : "false") + ",\"auxReady\":" + String(radioAuxReady(now) ? "true" : "false") + ",\"txCount\":" + String(radioTxCount) + ",\"rxCount\":" + String(radioRxCount) + ",\"rxBytes\":" + String(radioRxByteCount) + ",\"rxErrors\":" + String(radioRxErrors) + ",\"txErrors\":" + String(radioTxErrors) + ",\"rxAgeMs\":" + (radioRxCount ? String((uint32_t)(now - lastRadioRxMs)) : String("null")) + ",\"lastRx\":" + jsonString(lastRadioRx) + ",\"lastTx\":" + jsonString(lastRadioTx) + "}";
    if (statusSeen) {
      json += ",\"status\":{\"throttle\":" + String(rxThrottle) + ",\"roll\":" + String(rxRoll, 1) + ",\"pitch\":" + String(rxPitch, 1) + ",\"yaw\":" + String(rxYaw, 1) + ",\"motors\":[";
      for (int i = 0; i < 4; i++) {
        if (i) json += ',';
        json += String(rxMotors[i]);
      }
      json += "]}";
    }
    json += ",\"altHoldRequested\":true";
    json += ",\"altHoldClimb\":" + String(climbCommand);
    json += ",\"ps4Connected\":" + String(ps4 && ps4->isConnected() ? "true" : "false");
    json += ",\"ps4LY\":" + String(lastLY);
    json += ",\"homeRequested\":" + String(homeRequested ? "true" : "false");
    json += ",\"maxClimbCmS\":" + String(MAX_CLIMB_CM_S);
    json += '}';
    web.send(200, "application/json", json);
  });

  // The web slider cannot switch ALT_HOLD off or send direct motor PWM.
  web.on("/api/throttle", HTTP_POST, []() {
    respondError("PS4 altitude mode: direct PWM is disabled", 409);
  });

  web.on("/api/pids", HTTP_POST, []() {
    if (altHoldMode) {
      respondError("Tat ALT_HOLD truoc", 409);
      return;
    }
    if (operation != OP_NONE) {
      respondError("Đang có tác vụ PID khác", 409);
      return;
    }
    for (int i = 0; i < 5; i++) {
      if (!parseGain(web.arg(String(i) + "_kp"), pendingPids[i].kp) || !parseGain(web.arg(String(i) + "_ki"), pendingPids[i].ki) || !parseGain(web.arg(String(i) + "_kd"), pendingPids[i].kd)) {
        respondError("PID phải là số hữu hạn từ 0 đến 100");
        return;
      }
    }
    startOperation(OP_APPLY);
    respondOk();
  });

  web.on("/api/readpid", HTTP_POST, []() {
    if (altHoldMode) {
      respondError("Tat ALT_HOLD truoc", 409);
      return;
    }
    if (operation != OP_NONE) {
      respondError("Đang có tác vụ PID khác", 409);
      return;
    }
    startOperation(OP_READ);
    respondOk();
  });
  web.on("/api/althold", HTTP_POST, []() {
    respondError("ALT_HOLD is always on; PS4 controls altitude", 409);
  });

  web.onNotFound([]() {
    web.send(404, "text/plain", "Not found");
  });
}

void setup() {
  // Same Bluepad32 startup as the user's verified working PS4-only sketch.
  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32 PS4 Bluepad32 (BT-first / nonblocking Wi-Fi)");
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.enableVirtualDevice(false);
  Serial.println("Waiting for PS4 controller... (Wi-Fi is OFF for pairing)");

  altHoldMode = true;
  throttle = MIN_THR;
  climbCommand = 0;
  homeRequested = false;

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
  if (!radioStarted) {
    ++radioTxErrors;
    Serial.println("E220 UART initialization failed");
  }
  Serial.println("FW PS4_ALT_V2_BT_FIX: T,seq,1000,1,climb_cm_s,home");
  Serial.printf("E220: RX=%d TX=%d M0=%d M1=%d AUX=%d, %lu baud 8N1\n",
                E220_RX, E220_TX, E220_M0, E220_M1, E220_AUX,
                static_cast<unsigned long>(UART_BAUD));

  setupWebRoutes();
  // IMPORTANT: Do not call WiFi.begin() or wait for Wi-Fi in setup().
  // Bluepad32 callbacks run when BP32.update() executes in loop().
  lastTxMs = millis() - MIN_RADIO_GAP_MS;
  lastThrottleTxMs = millis() - THROTTLE_PERIOD_MS;
  lastWebMs = millis();
}

void maintainWiFi() {
#if PS4_DIAGNOSTIC_DISABLE_WIFI
  return;
#else
  static bool wasConnected = false;
  static uint32_t lastRetry = 0;
  const uint32_t now = millis();

  if (!wifiStarted) {
    if (ps4 == nullptr || !ps4->isConnected())
      return;
    if ((uint32_t)(now - ps4ConnectedSinceMs) < PS4_WIFI_START_DELAY_MS)
      return;

    // The controller has been fully registered by BP32.update() for 2 seconds.
    // Bring up Wi-Fi asynchronously while continuing to service BT in loop().
    wifiStarted = true;
    Serial.println("PS4 stable: starting Wi-Fi without blocking Bluepad32");
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(true);
    WiFi.setAutoReconnect(true);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    web.begin();
    lastRetry = millis();
    Serial.print("Connecting to Wi-Fi: ");
    Serial.println(WIFI_SSID);
    return;
  }

  const bool connected = WiFi.status() == WL_CONNECTED;
  if (connected && !wasConnected) {
    Serial.println("Wi-Fi connected");
    Serial.print("Dashboard: http://");
    Serial.println(WiFi.localIP());
  } else if (!connected && wasConnected) {
    Serial.println("Wi-Fi lost (PS4 input and E220 remain active)");
  }
  wasConnected = connected;
  if (!connected && (uint32_t)(now - lastRetry) >= WIFI_RETRY_MS) {
    lastRetry = now;
    Serial.println("Retrying Wi-Fi (nonblocking)...");
    WiFi.reconnect();
  }
#endif
}

void loop() {
  pollPS4();
  maintainWiFi();
  if (wifiStarted) web.handleClient();
  pollRadio();
  processRadioTx();

  static uint32_t lastDebug = 0;
  if (millis() - lastDebug >= 1000) {
    lastDebug = millis();
    Serial.printf(
      "E220 M0=%d M1=%d AUX=%d TX=%lu RX_FRAME=%lu RX_BYTE=%lu RX_ERR=%lu TX_ERR=%lu PS4=%d LY=%d CLIMB=%d HOME=%d STATUS_AGE=%lu S_VALID=%lu S_BAD=%lu OP=%d WAIT=%d\n",
      digitalRead(E220_M0), digitalRead(E220_M1),
      E220_AUX >= 0 ? digitalRead(E220_AUX) : -1,
      (unsigned long)radioTxCount,
      (unsigned long)radioRxCount,
      (unsigned long)radioRxByteCount,
      (unsigned long)radioRxErrors,
      (unsigned long)radioTxErrors,
      (int)(ps4 && ps4->isConnected()), (int)lastLY,
      (int)climbCommand, (int)homeRequested,
      (unsigned long)(statusSeen ? millis() - lastStatusMs : 0),
      (unsigned long)validStatusCount,
      (unsigned long)invalidStatusCount,
      (int)operation, (int)waiting);
  }
  delay(1);
}
