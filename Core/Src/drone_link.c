/* LoRa payload ASCII + *checksum XOR: nhan T, tra loi S/G/M (giao thuc v2). */
#include "drone_link.h"
#include "gps.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t xor_checksum(const char *data)
{
	uint8_t checksum = 0U;
	while (*data)
		checksum ^= (uint8_t)*data++;
	return checksum;
}

static bool send_payload(DroneLink_t *l, const char *payload)
{
	char packet[192];
	if (l->radio->tx_active || l->radio->huart->gState != HAL_UART_STATE_READY)
	{
		++l->tx_busy_count;
		return false;
	}
	int n = snprintf(packet, sizeof(packet), "%s*%02X\n", payload,
					 (unsigned)xor_checksum(payload));
	if (n <= 0 || n >= (int)sizeof(packet))
	{
		++l->tx_failed_count;
		return false;
	}
	HAL_StatusTypeDef rc = E220_Send_DMA(l->radio, (const uint8_t *)packet,
										 (uint16_t)n);
	if (rc == HAL_OK)
	{
		++l->tx_ok_count;
		return true;
	}
	if (rc == HAL_BUSY)
		++l->tx_busy_count;
	else
		++l->tx_failed_count;
	return false;
}

static bool validate_frame(char *s)
{
	size_t n = strlen(s);
	if (n < 4U || s[n - 3U] != '*')
		return false;
	char hex[3] = {s[n - 2U], s[n - 1U], '\0'};
	char *end = NULL;
	unsigned long checksum = strtoul(hex, &end, 16);
	if (end != hex + 2 || checksum > 255U)
		return false;
	s[n - 3U] = '\0';
	return xor_checksum(s) == (uint8_t)checksum;
}

static bool parse_u32(const char *s, uint32_t *value)
{
	if (!s || !*s || *s == '-')
		return false;
	char *end = NULL;
	unsigned long n = strtoul(s, &end, 10);
	if (end == s || *end || n > 0xFFFFFFFFUL)
		return false;
	*value = (uint32_t)n;
	return true;
}

static bool parse_climb(const char *s, int16_t *value)
{
	if (!s || !*s || !value)
		return false;
	char *end = NULL;
	long n = strtol(s, &end, 10);
	if (end == s || *end || n < -100L || n > 100L)
		return false;
	*value = (int16_t)n;
	return true;
}

static bool parse_int_range(const char *s, int16_t *out, long lower, long upper)
{
	if (!s || !*s || !out)
		return false;
	char *end = NULL;
	long n = strtol(s, &end, 10);
	if (end == s || *end || n < lower || n > upper)
		return false;
	*out = (int16_t)n;
	return true;
}

static bool handle_line(DroneLink_t *l, char *line)
{
	if (!validate_frame(line))
		return false;
	char *kind = strtok(line, ",");
	char *seq_s = strtok(NULL, ",");
	uint32_t seq;
	if (!kind || !parse_u32(seq_s, &seq))
		return false;

	if (strcmp(kind, "T") == 0)
	{
		uint32_t thr, mode = 0U;
		int16_t climb = 0, roll_sp = 0, pitch_sp = 0, yaw_sp = 0;
		const char *thr_s = strtok(NULL, ",");
		const char *mode_s = strtok(NULL, ",");
		if (!parse_u32(thr_s, &thr) || thr < DRONE_LINK_MIN_THR ||
			thr > DRONE_LINK_MAX_THR)
			return false;
		if (mode_s != NULL)
		{
			if (!parse_u32(mode_s, &mode) || mode > 2U)
				return false;
			const char *climb_s = strtok(NULL, ",");
			if (climb_s != NULL)
			{
				if (!parse_climb(climb_s, &climb))
					return false;
			}
			else if (mode != 0U)
			{
				return false;
			}
			if (mode == 2U)
			{
				if (!parse_int_range(strtok(NULL, ","), &roll_sp, -15, 15) || !parse_int_range(strtok(NULL, ","), &pitch_sp, -15, 15) || !parse_int_range(strtok(NULL, ","), &yaw_sp, -90, 90))
					return false;
				/* Mode 2 has a fixed nominal hover reference, not direct stick PWM. */
				if (thr != 1400U)
					return false;
			}
			/* Compatibility: T,seq,throttle,0 is MANUAL. */
		}
		if (strtok(NULL, ",") != NULL)
			return false;
		/* Previous frame T,seq,throttle remains MANUAL compatible. */
		l->throttle_us = (uint16_t)thr;
		l->alt_hold_requested = (mode == 1U || mode == 2U);
		l->auto_requested = (mode == 2U);
		l->climb_percent = l->alt_hold_requested ? climb : 0;
		l->roll_setpoint_deg = l->auto_requested ? roll_sp : 0;
		l->pitch_setpoint_deg = l->auto_requested ? pitch_sp : 0;
		l->yaw_rate_dps = l->auto_requested ? yaw_sp : 0;
		l->last_throttle_ms = HAL_GetTick();
		++l->throttle_rx_count;
		l->status_seq = seq;
		l->status_ready_ms = l->last_throttle_ms + DRONE_LINK_TURNAROUND_MS;
		l->status_pending = true;
		++l->status_request_count;
		return true;
	}
	/* P/G/A/N/R configuration frames intentionally unsupported. */
	return false;
}

void DroneLink_Init(DroneLink_t *l, E220_t *radio, AngleController_t *angle,
					RateController_t *rate)
{
	memset(l, 0, sizeof(*l));
	l->radio = radio;
	l->angle = angle;
	l->rate = rate;
	l->throttle_us = DRONE_LINK_MIN_THR;
	l->last_throttle_ms = HAL_GetTick();
}

void DroneLink_SetMinimumThrottle(DroneLink_t *l)
{
	l->throttle_us = DRONE_LINK_MIN_THR;
	/* Do not erase mode here: prevents silently rearming ALT_HOLD in main. */
	l->climb_percent = 0;
	l->roll_setpoint_deg = 0;
	l->pitch_setpoint_deg = 0;
	l->yaw_rate_dps = 0;
}

uint16_t DroneLink_Throttle(const DroneLink_t *l)
{
	if ((uint32_t)(HAL_GetTick() - l->last_throttle_ms) > DRONE_LINK_TIMEOUT_MS)
		return DRONE_LINK_MIN_THR;
	return l->throttle_us;
}

int16_t DroneLink_ClimbCommand(const DroneLink_t *l)
{
	if (l == NULL || !l->alt_hold_requested)
		return 0;
	if ((uint32_t)(HAL_GetTick() - l->last_throttle_ms) > DRONE_LINK_CLIMB_TIMEOUT_MS)
		return 0;
	return l->climb_percent;
}

/* Never retain flight-axis motion commands beyond the existing climb watchdog. */
static bool commands_fresh(const DroneLink_t *l)
{
	return l && l->auto_requested && (uint32_t)(HAL_GetTick() - l->last_throttle_ms) <= DRONE_LINK_CLIMB_TIMEOUT_MS;
}
int16_t DroneLink_RollCommand(const DroneLink_t *l)
{
	return commands_fresh(l) ? l->roll_setpoint_deg : 0;
}
int16_t DroneLink_PitchCommand(const DroneLink_t *l)
{
	return commands_fresh(l) ? l->pitch_setpoint_deg : 0;
}
int16_t DroneLink_YawRateCommand(const DroneLink_t *l)
{
	return commands_fresh(l) ? l->yaw_rate_dps : 0;
}

void DroneLink_Poll(DroneLink_t *l)
{
	E220_Service(l->radio);
	if ((uint32_t)(HAL_GetTick() - l->last_throttle_ms) > DRONE_LINK_TIMEOUT_MS && l->throttle_us != DRONE_LINK_MIN_THR)
	{
		++l->throttle_timeout_count;
		DroneLink_SetMinimumThrottle(l);
	}
	while (E220_Available(l->radio) != 0U)
	{
		char ch = (char)E220_ReadByte(l->radio);
		++l->rx_byte_count;
		if (ch == '\n')
		{
			++l->rx_line_count;
			if (!l->rx_discard && l->line_len != 0U)
			{
				l->line[l->line_len] = '\0';
				if (handle_line(l, l->line))
					++l->rx_valid_frames;
				else
					++l->rx_invalid_frames;
			}
			l->line_len = 0U;
			l->rx_discard = false;
		}
		else if (ch != '\r' && !l->rx_discard)
		{
			if (ch != '\0' && l->line_len < sizeof(l->line) - 1U)
				l->line[l->line_len++] = ch;
			else
			{
				l->line_len = 0U;
				l->rx_discard = true;
				++l->rx_invalid_frames;
			}
		}
	}
}

static long round_clamp(float x, float scale, long lo, long hi)
{
	if (!isfinite(x))
		return 0L;
	float v = x * scale;
	v += (v >= 0.0f) ? 0.5f : -0.5f;
	long n = (long)v;
	return n < lo ? lo : (n > hi ? hi : n);
}

/* Tao payload tra loi theo vi tri trong chu ky. Tra so byte hoac <= 0. */
static int build_reply(const DroneLink_t *l, const DroneLinkStatus_t *st,
					   char *payload, size_t size)
{
	const unsigned long seq = (unsigned long)l->status_seq;
	const uint32_t slot = l->reply_count % DRONE_LINK_REPLY_CYCLE;
	if (slot == 2U)
	{
		/* G: GPS. Khong fix -> toa do 0 (ESP KHONG duoc coi la vi tri). */
		const GPS_Data_t *gps = GPS_GetData();
		if (gps == NULL || !gps->fix)
			return snprintf(payload, size, "G,%lu,0,0,0,0,0,0", seq);
		return snprintf(payload, size, "G,%lu,1,%.6f,%.6f,%ld,%ld,%u", seq,
						gps->latitude, gps->longitude,
						round_clamp(gps->speed_kmh, 10.0f, 0L, 99999L),
						round_clamp(gps->course, 1.0f, 0L, 359L),
						(unsigned)gps->satellites);
	}
	if (slot == 4U)
	{
		/* M: motor + bo dem chan doan link (de tach mat T va mat S). */
		const E220_t *r = l->radio;
		return snprintf(payload, size, "M,%lu,%u,%u,%u,%u,%lu,%lu,%lu,%lu,%lu", seq,
						(unsigned)st->m1, (unsigned)st->m2, (unsigned)st->m3,
						(unsigned)st->m4,
						(unsigned long)l->throttle_rx_count,
						(unsigned long)l->rx_invalid_frames,
						(unsigned long)l->reply_late_drop_count,
						(unsigned long)(r ? r->uart_error_count : 0U),
						(unsigned long)(r ? r->rx_overflow_count : 0U));
	}
	/* S: chi cac truong dieu khien/an toan. Goc x10 (0.1 do), do cao cm. */
	long yaw = round_clamp(st->yaw_deg, 1.0f, 0L, 360L);
	if (yaw >= 360L)
		yaw = 0L;
	return snprintf(payload, size, "S,%lu,%u,%ld,%ld,%ld,%u,%ld,%u", seq,
					(unsigned)st->throttle_us,
					round_clamp(st->roll_deg, 10.0f, -1800L, 1800L),
					round_clamp(st->pitch_deg, 10.0f, -900L, 900L),
					yaw, (unsigned)st->flight_state,
					round_clamp(st->altitude_m, 100.0f, -99999L, 99999L),
					(unsigned)st->alt_exit_reason);
}

bool DroneLink_SendStatus(DroneLink_t *l, const DroneLinkStatus_t *st)
{
	if (l == NULL || st == NULL || !l->status_pending)
		return false; /* Slave: khong tu phat */
	const uint32_t now = HAL_GetTick();
	if ((int32_t)(now - l->status_ready_ms) < 0)
		return false; /* chua het turnaround */
	if ((uint32_t)(now - l->status_ready_ms) > DRONE_LINK_REPLY_MAX_LATE_MS)
	{
		l->status_pending = false; /* qua tre: bo, tranh phat chong T moi */
		++l->reply_late_drop_count;
		return false;
	}
	char payload[96];
	int n = build_reply(l, st, payload, sizeof(payload));
	if (n <= 0 || n >= (int)sizeof(payload) || !send_payload(l, payload))
		return false;
	l->status_pending = false;
	++l->reply_count;
	return true;
}
