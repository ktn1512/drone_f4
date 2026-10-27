#ifndef ALTITUDE_HOLD_H
#define ALTITUDE_HOLD_H

#include <stdint.h>

/* Altitude relative to the boot/home reference (meters).
 * climb_percent: -100 ... 0 ... +100; zero means lock current altitude.
 * All control functions run in main context, never inside an ISR.
 */
typedef struct {
    uint8_t active;
    uint8_t was_moving;
    float target_m;
    float altitude_m;
    float vz_mps;
    float vz_setpoint_mps;
    float trim_us;           /* Adaptive estimate of hover throttle. */
    float integral_us;
    float throttle_us;
    float last_altitude_m;
    uint32_t last_sample_ms;
} AltitudeHold_t;

void AltitudeHold_Reset(AltitudeHold_t *ctrl);

/* Start seamlessly at current throttle; no fixed hover value is required. */
uint8_t AltitudeHold_Start(AltitudeHold_t *ctrl,
                           float altitude_m,
                           float initial_throttle_us,
                           uint32_t sample_ms);

/* Call only for a NEW DPS310 pressure sample (~32 Hz).
 * Return 0 for invalid sample/timestamp; caller must exit ALT_HOLD.
 */
uint8_t AltitudeHold_Update(AltitudeHold_t *ctrl,
                            float altitude_m,
                            uint32_t sample_ms,
                            int16_t climb_percent);

#endif
