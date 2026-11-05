/* Lien ket LoRa: chi T/S ASCII + *checksum XOR. */
#ifndef DRONE_LINK_H
#define DRONE_LINK_H

#include "e220.h"
#include "angle_controller.h"
#include "rate_controller.h"
#include <stdbool.h>
#include <stdint.h>

#define DRONE_LINK_MIN_THR 1000U
#define DRONE_LINK_MAX_THR 1700U
#define DRONE_LINK_TIMEOUT_MS 4500U
/* Phai lon hon khoang cach 2 lenh T khi mat 1 goi S:
 * ESP REPLY_TIMEOUT_MS 1800 + guard 20 + ~150 ms truyen T ~= 1.97 s.
 * Doi REPLY_TIMEOUT_MS ben ESP32 thi phai doi lai so nay. */
#define DRONE_LINK_CLIMB_TIMEOUT_MS 2200U
/* Thay AUX: E220 vua xuat xong T ra UART -> doi ngan roi moi phat S. */
#define DRONE_LINK_TURNAROUND_MS 15U
/* S tre hon muc nay thi bo: ESP co the da timeout va sap phat T moi. */
#define DRONE_LINK_REPLY_MAX_LATE_MS 100U

/* Ly do ALT_HOLD tat, gui o truong cuoi goi S. ESP32 dung de phan biet
 * ha canh binh thuong (khong DUNG) voi loi (DUNG, can KICH HOAT LAI).
 * Phai khop voi ALT_EXIT_* trong esp32_drone_web.ino. */
typedef enum
{
    ALT_EXIT_NONE = 0,            /* dang bay / chua tung cat canh */
    ALT_EXIT_LANDED = 1,          /* ha canh binh thuong bang lenh XUONG */
    ALT_EXIT_BARO = 2,            /* DPS310 mat/khong hop le */
    ALT_EXIT_BARO_LATCHED = 3,    /* loi baro da chot, cho lenh mode moi */
    ALT_EXIT_UPDATE_FAULT = 4,    /* AltitudeHold_Update tu choi mau */
    ALT_EXIT_FAILSAFE_LANDED = 5, /* mat link, tu ha cham va da cham dat */
    ALT_EXIT_STOPPED = 6          /* ESP gui T mode 0 (DUNG) */
} AltExitReason_t;

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
/* S: thr = ga THAT dang ra mixer (khong phai so nhac lai lenh T),
 * cuoi goi them alt_exit_reason (AltExitReason_t). */
bool DroneLink_SendStatus(DroneLink_t *link, uint16_t throttle_us,
                          float roll, float pitch, float yaw,
                          uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4,
                          uint8_t alt_active, float altitude_m,
                          uint8_t alt_exit_reason);
#endif
