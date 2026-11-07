/* Flight mode (truc dung) cho AUTO (T mode 2): may trang thai ga.
 *
 * Thay cho khoi logic arm/cat canh/ha canh/khan cap truoc day nam trong main.c.
 * Muc tieu: KHONG con duong nao ha ga theo buoc (vd 1470 -> 1000 us) khi
 * drone co the con tren khong. Chi DUNG (mode 0) va mat IMU moi cat ngay.
 *
 *   DISARMED --(climb>0, link ok, baro ok)--> SPOOLUP --> TAKEOFF --(roi dat)--> ALT_HOLD
 *                                                                        |  ^
 *                                                          (climb < 0)   v  | (climb >= 0)
 *   DISARMED <--(idle giu 1 s)-- SPOOLDOWN <--(cham dat xac nhan)----- LANDING
 *   ALT_HOLD/LANDING --(baro loi)--> EMERGENCY --(het thoi gian)--> SPOOLDOWN
 *
 * Module thuan logic (khong goi HAL) de chay duoc test tren may tinh.
 * Khong thay doi he so PID trong altitude_hold.c.
 */
#ifndef FLIGHT_MODE_H
#define FLIGHT_MODE_H

#include <stdint.h>
#include "altitude_hold.h"

/* Ly do ALT_HOLD tat, gui trong goi S. Phai khop voi esp32_drone_web.ino. */
typedef enum
{
    ALT_EXIT_NONE = 0,            /* dang bay / chua tung cat canh */
    ALT_EXIT_LANDED = 1,          /* ha canh binh thuong / huy cat canh bang XUONG */
    ALT_EXIT_BARO = 2,            /* DPS310 mat/khong hop le (tren mat dat) */
    ALT_EXIT_BARO_LATCHED = 3,    /* baro loi khi dang bay -> ha khan cap */
    ALT_EXIT_UPDATE_FAULT = 4,    /* AltitudeHold_Update tu choi mau */
    ALT_EXIT_FAILSAFE_LANDED = 5, /* mat link, tu ha va da cham dat */
    ALT_EXIT_STOPPED = 6,         /* ESP gui T mode 0 (DUNG) */
    ALT_EXIT_EMERG_LANDED = 7,    /* ha canh khan cap vong ho da xong */
    ALT_EXIT_IMU = 8,             /* mat IMU, da cat motor */
    ALT_EXIT_TAKEOFF_FAIL = 9     /* het thoi gian cat canh ma khong roi dat */
} AltExitReason_t;

/* Gia tri trang thai gui trong goi S (truong fs). Khop esp32_drone_web.ino. */
typedef enum
{
    FM_DISARMED = 0,
    FM_SPOOLUP = 1,
    FM_TAKEOFF = 2,
    FM_ALT_HOLD = 3,
    FM_LANDING = 4,
    FM_SPOOLDOWN = 5,
    FM_EMERGENCY = 6
} FlightState_t;

typedef struct
{
    uint32_t now_ms;
    float dt_s;            /* chu ky dieu khien thuc (s) */
    uint8_t auto_mode;     /* T mode 2 dang duoc yeu cau */
    uint8_t link_lost;     /* qua LINK_LOST_MS khong co T */
    int16_t climb_cmd;     /* -100..100, da ap failsafe (-60 khi mat link) */
    uint8_t baro_healthy;  /* home hop le, mau moi <= 180 ms, huu han */
    uint8_t baro_new;      /* co mau DPS310 MOI trong chu ky nay */
    float baro_alt_m;      /* do cao tuong doi home (m) */
    uint32_t baro_sample_ms;
    float accel_norm_g;    /* |a| tu IMU (g), dung xac nhan cham dat */
} FlightInputs_t;

typedef struct
{
    FlightState_t state;
    AltitudeHold_t alt;
    uint8_t exit_reason;     /* AltExitReason_t */
    uint8_t fault_latched;   /* cho lenh mode moi (DUNG -> KICH HOAT LAI) */
    uint8_t prev_auto;

    float throttle_us;       /* dau ra cuoi (sau bo gioi han giam ga) */
    float target_us;         /* ga trang thai yeu cau (truoc bo gioi han) */
    float state_thr_us;      /* ga noi bo SPOOLUP/TAKEOFF/SPOOLDOWN/EMERGENCY */
    uint32_t state_since_ms;
    uint32_t cond_since_ms;  /* hen gio xac nhan roi dat / cham dat / giu idle */

    float ground_alt_m;      /* baro luc bat dau SPOOLUP */
    float hover_ref_us;      /* ga treo: gia tri doan, hoc them khi bay that */
    uint8_t hover_learned;
    uint32_t airborne_since_ms;

    /* Van toc dung tu baro, cap nhat moi mau (doc lap voi ALT_HOLD). */
    float baro_vz_mps;
    float baro_last_alt_m;
    uint32_t baro_last_ms;
    uint8_t baro_vz_valid;

    float accel_lpf_g;       /* |a| loc tau 0.5 s */
    float land_vz_lpf;

    float emerg_start_us;
    uint32_t emerg_duration_ms;

    uint32_t fault_count;
} FlightMode_t;

void FlightMode_Init(FlightMode_t *fm);
void FlightMode_Step(FlightMode_t *fm, const FlightInputs_t *in);
/* Cat motor NGAY (chi dung khi mat IMU): khong giu duoc tu the. */
void FlightMode_Kill(FlightMode_t *fm, uint8_t reason);
/* 1 khi lenh roll/pitch/yaw tu LoRa duoc phep tac dong (dang bay). */
uint8_t FlightMode_AttitudeCmdEnabled(const FlightMode_t *fm);
/* 1 khi motor dang chay co dieu khien (bao ESP la "active"). */
uint8_t FlightMode_Active(const FlightMode_t *fm);

#endif
