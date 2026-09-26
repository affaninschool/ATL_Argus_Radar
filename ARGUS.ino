/* ═══════════════════════════════════════════════════════════════
   ARGUS — PERIMETER AWARENESS ARRAY  (with Serial Telemetry)
   Board : ESP8266 MOD (D1 mini) · HC-SR04 · SG90
   AP    : ATL-RADAR  →  http://192.168.4.1
   Files : ARGUS.ino (this) + page.h (dashboard)
   ═══════════════════════════════════════════════════════════════ */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include "page.h"

/* ── PIN MAP ─────────────────────────────────────────────── */
#define PIN_SERVO   5      // D1  → SG90 signal (orange)
#define PIN_TRIG    4      // D2  → HC-SR04 Trig
#define PIN_ECHO   14      // D5  → HC-SR04 Echo (via 1k/2k divider!)
#define PIN_GREEN  12      // D6  → Green LED
#define PIN_RED    13      // D7  → Red LED

/* ── ACCESS POINT ────────────────────────────────────────── */
const char* AP_SSID = "ATL-RADAR";
const char* AP_PASS = "argus2024";

/* ── RADAR CONFIG ────────────────────────────────────────── */
#define MAX_RANGE_CM     50
#define ALERT_CM         20
#define SWEEP_MIN         0
#define SWEEP_MAX       180
#define PING_TIMEOUT_US  30000UL

/* ── SERIAL TELEMETRY OPTIONS ────────────────────────────── */
#define SERIAL_VERBOSE      1     // 1 = print every sweep step, 0 = off
#define SERIAL_STATS_EVERY  4     // print a stats line every N full sweeps

/* ── STATE ───────────────────────────────────────────────── */
ESP8266WebServer server(80);
Servo sweepServo;

int  g_angle        = 0;
int  g_dir          = 1;
bool g_scanRunning  = true;
int  g_distance     = MAX_RANGE_CM;
bool g_detected     = false;

int  g_tickMs       = 30;    // sweep tick interval (adjustable via /speed)
int  g_step         = 3;     // degrees per step  (adjustable via /speed)
int  g_speedLevel   = 2;     // 1=Slow, 2=Medium, 3=Fast

unsigned long g_lastSweep = 0;

/* ── TELEMETRY COUNTERS ──────────────────────────────────── */
unsigned long g_stepCount     = 0;   // total sweep steps since boot
unsigned long g_hitCount      = 0;   // total target detections
unsigned long g_alertCount    = 0;   // total alerts (<= ALERT_CM)
unsigned long g_sweepCount    = 0;   // total full sweeps (0→180→0)
int           g_minSeen       = 999; // smallest distance seen
bool          g_lastDir       = true;// track direction flips for sweep count

/* ═══════════════════════════════════════════════════════════
   ULTRASONIC — median of 3
   ═══════════════════════════════════════════════════════════ */
int pingOnce() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(3);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long dur = pulseIn(PIN_ECHO, HIGH, PING_TIMEOUT_US);
  if (dur == 0) return -1;
  return (int)(dur * 0.0343f / 2.0f);
}

int pingFiltered() {
  int a = pingOnce(); delay(6);
  int b = pingOnce(); delay(6);
  int c = pingOnce();

  int v[3]; int n = 0;
  if (a > 0) v[n++] = a;
  if (b > 0) v[n++] = b;
  if (c > 0) v[n++] = c;
  if (n == 0) return -1;
  if (n == 1) return v[0];
  if (n == 2) return (v[0] + v[1]) / 2;

  if (v[0] > v[1]) { int t=v[0]; v[0]=v[1]; v[1]=t; }
  if (v[1] > v[2]) { int t=v[1]; v[1]=v[2]; v[2]=t; }
  if (v[0] > v[1]) { int t=v[0]; v[0]=v[1]; v[1]=t; }
  return v[1];
}

/* ═══════════════════════════════════════════════════════════
   LED FEEDBACK
   ═══════════════════════════════════════════════════════════ */
void updateLEDs(bool alert) {
  digitalWrite(PIN_RED,   alert ? HIGH : LOW);
  digitalWrite(PIN_GREEN, alert ? LOW  : HIGH);
}

/* ═══════════════════════════════════════════════════════════
   SERIAL HELPERS
   ═══════════════════════════════════════════════════════════ */
void printPad3(int v, char* buf) {
  // 0 -> "  0", 45 -> " 45", 180 -> "180"
  if (v < 10)       sprintf(buf, "  %d", v);
  else if (v < 100) sprintf(buf, " %d", v);
  else              sprintf(buf, "%d", v);
}

void serialStepLine(int angle, int cm, bool detected, bool alert) {
#if SERIAL_VERBOSE
  char angBuf[5];
  printPad3(angle, angBuf);

  char distBuf[8];
  if (cm <= 0 || cm > MAX_RANGE_CM) strcpy(distBuf, " ---");
  else                              sprintf(distBuf, "%3d", cm);

  const char* tgt = detected ? "TGT" : "   ";
  const char* led = alert    ? "RED" : (detected ? "GRN" : "GRN");
  const char* flag = alert   ? "⚠ ALERT" : (detected ? "· track" : "· clear");

  Serial.printf("[%5lu] ANG %s°  |  DIST %s cm  |  %s  |  LED %s  |  %s\n",
                g_stepCount, angBuf, distBuf, tgt, led, flag);
#endif
}

void serialStatsLine() {
  Serial.println(F("────────────────────────────────────────────────────────────"));
  Serial.printf("  SWEEPS: %lu   STEPS: %lu   TARGETS: %lu   ALERTS: %lu   MIN: %d cm   UPTIME: %lu s\n",
                g_sweepCount, g_stepCount, g_hitCount, g_alertCount,
                (g_minSeen == 999 ? 0 : g_minSeen),
                (unsigned long)(millis() / 1000));
  Serial.println(F("────────────────────────────────────────────────────────────"));
}

/* ═══════════════════════════════════════════════════════════
   SWEEP STEP  (non-blocking)
   ═══════════════════════════════════════════════════════════ */
void sweepStep() {
  if (!g_scanRunning) return;
  if (millis() - g_lastSweep < (unsigned long)g_tickMs) return;
  g_lastSweep = millis();

  sweepServo.write(g_angle);
  delay(8);
  int cm = pingFiltered();

  bool det   = (cm > 0 && cm <= MAX_RANGE_CM);
  bool alert = det && (cm <= ALERT_CM);

  g_distance = det ? cm : MAX_RANGE_CM;
  g_detected = det;

  updateLEDs(alert);

  /* ── telemetry ── */
  g_stepCount++;
  if (det) {
    g_hitCount++;
    if (cm < g_minSeen) g_minSeen = cm;
  }
  if (alert) g_alertCount++;

  serialStepLine(g_angle, det ? cm : -1, det, alert);

  /* ── advance angle ── */
  g_angle += g_dir * g_step;
  if (g_angle >= SWEEP_MAX) {
    g_angle = SWEEP_MAX;
    if (g_dir != -1) { /* just turned around */
      g_sweepCount++;
      if (g_sweepCount % SERIAL_STATS_EVERY == 0) serialStatsLine();
    }
    g_dir = -1;
  }
  if (g_angle <= SWEEP_MIN) {
    g_angle = SWEEP_MIN;
    g_dir = 1;
  }
}

/* ═══════════════════════════════════════════════════════════
   HTTP HANDLERS
   ═══════════════════════════════════════════════════════════ */
void handleRoot() {
  server.sendHeader("Cache-Control", "no-store");
  server.send_P(200, "text/html", ARGUS_PAGE);
}

void handleData() {
  String j = "{";
  j += "\"angle\":"    + String(g_angle)                          + ",";
  j += "\"distance\":" + String(g_distance)                       + ",";
  j += "\"detected\":" + String(g_detected ? "true" : "false")    + ",";
  j += "\"running\":"  + String(g_scanRunning ? "true" : "false") + ",";
  j += "\"speed\":"    + String(g_speedLevel)                     + ",";
  j += "\"clients\":"  + String(WiFi.softAPgetStationNum());
  j += "}";
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", j);
}

void handleScanToggle() {
  g_scanRunning = !g_scanRunning;
  Serial.print(F("  >> SCAN "));
  Serial.println(g_scanRunning ? F("RESUMED") : F("PAUSED"));
  String j = "{\"running\":" + String(g_scanRunning ? "true" : "false") + "}";
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", j);
}

void handleSpeed() {
  int v = server.arg("v").toInt();
  if      (v == 1) { g_tickMs = 45; g_step = 2; g_speedLevel = 1; }
  else if (v == 3) { g_tickMs = 18; g_step = 4; g_speedLevel = 3; }
  else             { v = 2; g_tickMs = 30; g_step = 3; g_speedLevel = 2; }

  const char* names[] = { "?", "SLOW", "MEDIUM", "FAST" };
  Serial.print(F("  >> SPEED = "));
  Serial.print(names[v]);
  Serial.print(F("  (tick="));
  Serial.print(g_tickMs);
  Serial.print(F(" ms, step="));
  Serial.print(g_step);
  Serial.println(F("°)"));

  String j = "{\"speed\":" + String(v) + "}";
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", j);
}

/* ═══════════════════════════════════════════════════════════
   SETUP
   ═══════════════════════════════════════════════════════════ */
void setup() {
  Serial.begin(115200);
  delay(200);

  Serial.println();
  Serial.println(F("╔══════════════════════════════════════════════════════════╗"));
  Serial.println(F("║           ARGUS — PERIMETER AWARENESS ARRAY              ║"));
  Serial.println(F("║           ESP8266 MOD (D1 mini) · HC-SR04 · SG90         ║"));
  Serial.println(F("╚══════════════════════════════════════════════════════════╝"));
  Serial.println();
  Serial.println(F("  PIN MAP"));
  Serial.println(F("  ─────────────────────────────────────────────────────"));
  Serial.println(F("  D1  GPIO5   Servo signal"));
  Serial.println(F("  D2  GPIO4   HC-SR04 Trig"));
  Serial.println(F("  D5  GPIO14  HC-SR04 Echo  (via 1k/2k divider)"));
  Serial.println(F("  D6  GPIO12  Green LED"));
  Serial.println(F("  D7  GPIO13  Red LED"));
  Serial.println();
  Serial.println(F("  RADAR CONFIG"));
  Serial.println(F("  ─────────────────────────────────────────────────────"));
  Serial.printf ("  Max range      : %d cm\n", MAX_RANGE_CM);
  Serial.printf ("  Alert threshold: %d cm\n", ALERT_CM);
  Serial.printf ("  Sweep range    : %d° → %d°\n", SWEEP_MIN, SWEEP_MAX);
  Serial.printf ("  Step size      : %d°\n", g_step);
  Serial.printf ("  Tick interval  : %d ms\n", g_tickMs);
  Serial.println();

  /* pins */
  pinMode(PIN_TRIG,  OUTPUT);
  pinMode(PIN_ECHO,  INPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_RED,   OUTPUT);
  digitalWrite(PIN_TRIG, LOW);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_RED,   LOW);

  /* servo */
  Serial.print(F("  Servo init ... "));
  sweepServo.attach(PIN_SERVO);
  sweepServo.write(0);
  delay(400);
  Serial.println(F("OK"));

  /* access point */
  Serial.print(F("  Starting AP ... "));
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(200);
  Serial.println(F("OK"));
  Serial.println();
  Serial.print(F("  AP SSID : ")); Serial.println(AP_SSID);
  Serial.print(F("  AP PASS : ")); Serial.println(AP_PASS);
  Serial.print(F("  AP IP   : ")); Serial.println(WiFi.softAPIP());
  Serial.println();

  /* routes */
  server.on("/",       HTTP_GET, handleRoot);
  server.on("/data",   HTTP_GET, handleData);
  server.on("/scan",   HTTP_GET, handleScanToggle);
  server.on("/speed",  HTTP_GET, handleSpeed);
  server.onNotFound([]() { server.send(404, "text/plain", "Not found"); });

  server.begin();
  Serial.println(F("  HTTP server up → http://192.168.4.1"));
  Serial.println();
  Serial.println(F("════════════════════════════════════════════════════════════"));
  Serial.println(F("  TELEMETRY START — live sweep log below"));
  Serial.println(F("  Format: [step] ANG xxx° | DIST xxx cm | TGT | LED | state"));
  Serial.println(F("════════════════════════════════════════════════════════════"));
  Serial.println();
}

/* ═══════════════════════════════════════════════════════════
   LOOP
   ═══════════════════════════════════════════════════════════ */
void loop() {
  server.handleClient();
  sweepStep();
}