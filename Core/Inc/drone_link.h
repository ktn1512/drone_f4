/* Lien ket LoRa: T (ESP->STM) va S/G/M (STM->ESP) ASCII + *checksum XOR.
 * Giao thuc v2 (rut gon goi tra loi de giam thoi gian phat song):
 *   S,seq,thr,roll10,pitch10,yaw,fs,alt_cm,exit          (~30-40 byte)
 *   G,seq,fix,lat,lon,speed10_kmh,course,sats            (~25-50 byte)
 *   M,seq,m1,m2,m3,m4,rxT,rxBad,late,uerr,rxovf          (~45-55 byte)
 * Moi T chi duoc tra loi DUNG MOT goi: chu ky S,S,G,S,M (xem
 * DRONE_LINK_REPLY_CYCLE). Phai khop esp32_drone_web.ino. */
#ifndef DRONE_LINK_H
#define DRONE_LINK_H

#include "e220.h"
#include "angle_controller.h"
#include "rate_controller.h"
#include "flight_mode.h" /* AltExitReason_t, FlightState_t */
#include <stdbool.h>
#include <stdint.h>

#define DRONE_LINK_MIN_THR 1000U
#define DRONE_LINK_MAX_THR 1700U
#define DRONE_LINK_TIMEOUT_MS 4500U
/* Rang buoc thoi gian (RTT do duoc voi goi S cu 86 byte: ~1185 ms;
 * goi tra loi v2 <= ~55 byte nen RTT phai NHO HON, can do lai bang RTTmax).
 * Khoang cach 2 lenh T khi ESP het cho 1 phien:
 *   REPLY_TIMEOUT_MS(1300) + guard 20 + ~26 ms day T vao UART ~= 1.35 s.
 * Climb/roll/pitch/yaw tu bo sau 1.6 s (> 1 phien hong, < 2 phien hong).
 * Doi REPLY_TIMEOUT_MS ben ESP32 thi phai doi lai so nay va LINK_LOST_MS. */
#define DRONE_LINK_CLIMB_TIMEOUT_MS 1600U
/* Thay AUX: E220 vua xuat xong T ra UART -> doi ngan roi moi phat S. */
#define DRONE_LINK_TURNAROUND_MS 15U
/* S tre hon muc nay thi bo: ESP co the da timeout va sap phat T moi. */
#define DRONE_LINK_REPLY_MAX_LATE_MS 100U

/* So thu tu goi tra loi trong chu ky: vi tri 2 -> G (GPS), 4 -> M (motor +
 * chan doan), con lai -> S. S chiem 3/5 phien, khoang cach S toi da 2 phien. */
#define DRONE_LINK_REPLY_CYCLE 5U

/* Du lieu cho goi tra loi (STM -> ESP). */
typedef struct
{
    uint16_t throttle_us; /* ga THAT dang ra mixer */
    float roll_deg, pitch_deg, yaw_deg;
    uint16_t m1, m2, m3, m4;
    uint8_t flight_state;    /* FlightState_t */
    float altitude_m;
    uint8_t alt_exit_reason; /* AltExitReason_t */
} DroneLinkStatus_t;

typedef struct
{
    E220_t *radio;
    AngleController_t *angle;
    RateController_t *rate;
    char line[128];
    uint16_t line_len;
    bool rx_discard;
    uint16_t throttle_us;
    uint32_t last_throttle_ms;

    /* T: mode 0=DUNG (motor 1000), 1=legacy ALT_HOLD (bo qua),
     * 2=AUTO cat canh/giu do cao.
     * Mode 2: T,seq,1400,2,climb_pct,roll_deg,pitch_deg,yaw_dps. */
    bool alt_hold_requested;
    /* AUTO cat canh + giu do cao: mode=2. */
    bool auto_requested;
    int16_t climb_percent;
    int16_t roll_setpoint_deg;
    int16_t pitch_setpoint_deg;
    int16_t yaw_rate_dps;

    bool status_pending;
    uint32_t status_seq;

    uint32_t status_ready_ms;
    uint32_t reply_late_drop_count;
    uint32_t reply_count; /* so goi tra loi da phat, chon S/G/M */

    uint32_t rx_byte_count;
    uint32_t rx_line_count;
    uint32_t rx_valid_frames;
    uint32_t rx_invalid_frames;
    uint32_t throttle_rx_count;
    uint32_t throttle_timeout_count;
    /* Legacy diagnostic counters used by unchanged main.c, always zero. */
    uint32_t pid_write_count;
    uint32_t pid_read_count;
    uint32_t status_request_count;
    uint32_t tx_ok_count;
    uint32_t tx_busy_count;
    uint32_t tx_failed_count;
} DroneLink_t;

void DroneLink_Init(DroneLink_t *link, E220_t *radio,
                    AngleController_t *angle, RateController_t *rate);
void DroneLink_Poll(DroneLink_t *link);
void DroneLink_SetMinimumThrottle(DroneLink_t *link);
uint16_t DroneLink_Throttle(const DroneLink_t *link);
int16_t DroneLink_ClimbCommand(const DroneLink_t *link);
int16_t DroneLink_RollCommand(const DroneLink_t *link);
int16_t DroneLink_PitchCommand(const DroneLink_t *link);
int16_t DroneLink_YawRateCommand(const DroneLink_t *link);
/* Tra loi T dang cho bang S, G hoac M (xem DRONE_LINK_REPLY_CYCLE). */
bool DroneLink_SendStatus(DroneLink_t *link, const DroneLinkStatus_t *st);
#endif
