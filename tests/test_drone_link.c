/* Host test giao thuc LoRa v2 (drone_link.c that, HAL/E220/GPS stub).
 * Kiem tra: chu ky S,S,G,S,M; checksum; do dai goi; ESP parse duoc bang
 * dung chuoi sscanf trong esp32_drone_web.ino. */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "drone_link.h"
#include "gps.h"

static int failures;
#define CHECK(c, ...) do { if (!(c)) { ++failures; printf("FAIL %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"); } } while (0)

/* ---- stub ---- */
static uint32_t tick = 1000U;
uint32_t HAL_GetTick(void) { return tick; }
static char rx_q[512]; static size_t rx_len, rx_pos;
static char last_tx[300]; static int last_tx_len;
HAL_StatusTypeDef E220_Send_DMA(E220_t *e, const uint8_t *d, uint16_t n)
{ (void)e; memcpy(last_tx, d, n); last_tx[n] = '\0'; last_tx_len = n; return HAL_OK; }
void E220_Service(E220_t *e) { (void)e; }
uint16_t E220_Available(E220_t *e) { (void)e; return (uint16_t)(rx_len - rx_pos); }
uint8_t E220_ReadByte(E220_t *e) { (void)e; return (uint8_t)rx_q[rx_pos++]; }
static GPS_Data_t gps;
GPS_Data_t *GPS_GetData(void) { return &gps; }

static uint8_t xorsum(const char *s, size_t n) { uint8_t c = 0; for (size_t i = 0; i < n; ++i) c ^= (uint8_t)s[i]; return c; }

static void feed_T(uint32_t seq)
{
    char p[64], f[80];
    snprintf(p, sizeof p, "T,%lu,1400,2,-100,-12,-12,-60", (unsigned long)seq);
    snprintf(f, sizeof f, "%s*%02X\n", p, xorsum(p, strlen(p)));
    rx_len = rx_pos = 0; memcpy(rx_q, f, strlen(f)); rx_len = strlen(f);
}

/* Giai ma giong decodeFrame() ben ESP: tra payload hoac NULL. */
static char *decode(char *frame)
{
    size_t n = strlen(frame);
    if (n < 5 || frame[n - 1] != '\n' || frame[n - 4] != '*') return NULL;
    unsigned want; if (sscanf(frame + n - 3, "%2X", &want) != 1) return NULL;
    frame[n - 4] = '\0';
    return xorsum(frame, n - 4) == want ? frame : NULL;
}

int main(void)
{
    E220_t radio; UART_HandleTypeDef hu; memset(&radio, 0, sizeof radio); memset(&hu, 0, sizeof hu);
    hu.gState = HAL_UART_STATE_READY; radio.huart = &hu;
    radio.uart_error_count = 99999; radio.rx_overflow_count = 99999;
    DroneLink_t link; AngleController_t a; RateController_t r;
    DroneLink_Init(&link, &radio, &a, &r);

    /* Truong hop xau nhat cho do dai. */
    gps.fix = 1; gps.latitude = -89.123456; gps.longitude = -179.123456;
    gps.speed_kmh = 999.9f; gps.course = 359.6f; gps.satellites = 99;
    DroneLinkStatus_t st = { 1700, -179.96f, -89.96f, 359.6f, 1700, 1700, 1700, 1700,
                             FM_EMERGENCY, -999.99f, ALT_EXIT_TAKEOFF_FAIL };
    const char expect[] = "SSGSMSSGSM";
    int maxlen[3] = {0, 0, 0};
    for (int i = 0; i < 10; ++i)
    {
        uint32_t seq = 4294967290UL + (uint32_t)i; /* seq lon nhat (10 chu so) */
        feed_T(seq);
        DroneLink_Poll(&link);
        CHECK(link.status_pending, "T %d khong duoc chap nhan", i);
        tick += DRONE_LINK_TURNAROUND_MS;
        last_tx_len = 0;
        CHECK(DroneLink_SendStatus(&link, &st), "khong gui tra loi %d", i);
        tick += 500U;
        char fr[300]; strcpy(fr, last_tx);
        int len = last_tx_len;
        char *p = decode(fr);
        CHECK(p != NULL, "checksum/khung sai: %s", last_tx);
        if (!p) continue;
        CHECK(p[0] == expect[i], "goi %d la %c, mong doi %c", i, p[0], expect[i]);
        unsigned long s2 = 0; int pos = 0;
        if (p[0] == 'S') {
            unsigned thr, fs, ex; int rr, pp, yy, alt;
            int n = sscanf(p, "S,%lu,%u,%d,%d,%d,%u,%d,%u%n", &s2, &thr, &rr, &pp, &yy, &fs, &alt, &ex, &pos);
            CHECK(n == 8 && pos == (int)strlen(p), "ESP khong parse duoc S: %s", p);
            CHECK(thr == 1700 && rr == -1800 && pp == -900 && yy == 0 && fs == FM_EMERGENCY && alt == -99999 && ex == 9,
                  "gia tri S sai: %s", p);
            if (len > maxlen[0]) maxlen[0] = len;
        } else if (p[0] == 'G') {
            unsigned fix, sats; double lat, lon; long spd, crs;
            int n = sscanf(p, "G,%lu,%u,%lf,%lf,%ld,%ld,%u%n", &s2, &fix, &lat, &lon, &spd, &crs, &sats, &pos);
            CHECK(n == 7 && pos == (int)strlen(p), "ESP khong parse duoc G: %s", p);
            CHECK(fix == 1 && fabs(lat + 89.123456) < 1e-6 && spd == 9999 && crs == 359 && sats == 99, "gia tri G sai: %s", p);
            if (len > maxlen[1]) maxlen[1] = len;
        } else if (p[0] == 'M') {
            unsigned m1, m2, m3, m4; unsigned long rxT, bad, late, uerr, ovf;
            int n = sscanf(p, "M,%lu,%u,%u,%u,%u,%lu,%lu,%lu,%lu,%lu%n", &s2, &m1, &m2, &m3, &m4, &rxT, &bad, &late, &uerr, &ovf, &pos);
            CHECK(n == 10 && pos == (int)strlen(p), "ESP khong parse duoc M: %s", p);
            CHECK(rxT == (unsigned long)(i + 1) && uerr == 99999, "bo dem M sai: %s", p);
            if (len > maxlen[2]) maxlen[2] = len;
        }
        CHECK(s2 == seq, "seq tra loi %lu != %lu", s2, (unsigned long)seq);
        if (i == 0) printf("vd S: %s", last_tx);
        if (i == 2) printf("vd G: %s", last_tx);
        if (i == 4) printf("vd M: %s", last_tx);
    }
    printf("do dai lon nhat (byte, ke ca *CS\\n): S=%d G=%d M=%d (goi S cu ~86-120)\n",
           maxlen[0], maxlen[1], maxlen[2]);
    CHECK(maxlen[0] <= 48 && maxlen[1] <= 60 && maxlen[2] <= 72, "goi qua dai");

    /* Tra loi tre qua 100 ms phai bi bo, khong phat chong T moi. */
    feed_T(1); DroneLink_Poll(&link);
    tick += DRONE_LINK_TURNAROUND_MS + DRONE_LINK_REPLY_MAX_LATE_MS + 1U;
    CHECK(!DroneLink_SendStatus(&link, &st) && !link.status_pending, "khong bo tra loi tre");

    /* Khong fix: G gui 0 va fix=0. */
    gps.fix = 0;
    for (int i = 0; i < 5; ++i) {
        feed_T(100U + (uint32_t)i); DroneLink_Poll(&link); tick += DRONE_LINK_TURNAROUND_MS;
        (void)DroneLink_SendStatus(&link, &st); tick += 500U;
        if (last_tx[0] == 'G') CHECK(strncmp(last_tx, "G,", 2) == 0 && strstr(last_tx, ",0,0,0,0,0,0*"), "G khong fix sai: %s", last_tx);
    }
    if (failures) { printf("%d FAILURE(S)\n", failures); return 1; }
    printf("ALL DRONE LINK TESTS PASSED\n");
    return 0;
}
