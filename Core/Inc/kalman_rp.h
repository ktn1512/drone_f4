#ifndef KALMAN_RP_H
#define KALMAN_RP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Kalman 1 trang thai: goc (deg).
 * Gyro (deg/s) dung de du doan; goc accel (deg) de hieu chinh.
 * Cac gia tri Q/R la PHUONG SAI, khong phai he so PID.
 * Dung gyro DA TRU BIAS. Khong su dung cho Yaw.
 */
typedef struct {
    float angle_deg;
    float variance_deg2;
    float gyro_noise_dps2;  /* Q: (deg/s)^2, default = 1.0 */
    float accel_noise_deg2; /* R: deg^2, default = 9.0 */
    float last_gain;
    uint32_t accel_used_count;
    uint32_t accel_rejected_count;
    uint8_t initialized;
} Kalman1D_t;

typedef struct {
    Kalman1D_t roll;
    Kalman1D_t pitch;
    float acc_roll_deg;
    float acc_pitch_deg;
    float accel_norm_g;
    float accel_weight;
    uint8_t initialized;
} KalmanRP_t;

/* Qua trinh ban dau tu accel dang dung yen; tra ve 1 neu hop le. */
uint8_t KalmanRP_Init(KalmanRP_t *filter, float ax_g, float ay_g, float az_g);

/* Q = gyro_noise_dps^2, R = accel_noise_deg^2; 1.0 / 3.0 giong ESP32_FC.
 * Tra ve 0 neu gia tri khong hop le; giu nguyen cac he so truoc do.
 */
uint8_t KalmanRP_SetNoise(KalmanRP_t *filter,
                          float gyro_noise_dps, float accel_noise_deg);

/* Call sau ICM42670_ApplyCalibration(), moi chu ky PID, dt_s do thuc te.
 * Gia toc giong he truc Mahony_InitFromAccel:
 *   roll=atan2(ay,az); pitch=atan2(-ax,sqrt(ay^2+az^2)).
 * Accel co norm lech 1g >0.2g: bo phep do gia toc, van du doan bang gyro.
 * Neu dt hoac gyro loi: return 0, KHONG cap nhat trang thai.
 * Cap nhat thanh cong: return 1.
 */
uint8_t KalmanRP_Update(KalmanRP_t *filter,
                        float gx_dps, float gy_dps,
                        float ax_g, float ay_g, float az_g,
                        float dt_s);

#ifdef __cplusplus
}
#endif
#endif
