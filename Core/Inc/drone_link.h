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
#define DRONE_LINK_CLIMB_TIMEOUT_MS 900U

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

    /* T: mode 0=MANUAL, 1=web ALT_HOLD, 2=PS4 auto takeoff/hold.
     * Mode 2: T,seq,1400,2,climb_pct,roll_deg,pitch_deg,yaw_dps. */
    bool alt_hold_requested;
    /* PS4 auto takeoff + climb: mode=2, distinct from legacy web mode=1. */
    bool ps4_auto_requested;
    int16_t climb_percent;
    int16_t roll_setpoint_deg;
    int16_t pitch_setpoint_deg;
    int16_t yaw_rate_dps;

    bool status_pending;
    uint32_t status_seq;

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
bool DroneLink_SendStatus(DroneLink_t *link, float roll, float pitch, float yaw,
                          uint16_t m1, uint16_t m2, uint16_t m3, uint16_t m4,
                          uint8_t alt_active, float altitude_m);
#endif
