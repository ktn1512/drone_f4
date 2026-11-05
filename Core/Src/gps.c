/* Nonblocking GPS over USART1 (38400 8N1, interrupt RX).
 * ISR only queues bytes; NMEA checksum validation and RMC/GGA parsing happen
 * in GPS_Process() from main context, leaving the 500 Hz flight loop intact.
 */
#include "gps.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define GPS_NMEA_LINE_SIZE 128U
#define GPS_RX_FIFO_SIZE   512U   /* Power of two, keeps ISR short. */
#define GPS_RMC_STALE_MS  2500U
#define GPS_BYTES_PER_POLL 192U

static UART_HandleTypeDef *gps_uart;
static uint8_t gps_rx_byte;
static volatile uint8_t gps_need_rearm;
static volatile uint16_t gps_head, gps_tail;
static uint8_t gps_fifo[GPS_RX_FIFO_SIZE];
static char gps_line[GPS_NMEA_LINE_SIZE];
static uint16_t gps_line_len;
static uint8_t gps_discard_line;
static GPS_Data_t gps_data;

static int hex_digit(char ch)
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    return -1;
}

/* Check $...*HH checksum before touching any navigation values. */
static uint8_t nmea_checksum_ok(char *line)
{
    if (line[0] != '$') return 0U;
    char *star = strchr(line, '*');
    if (!star || !star[1] || !star[2] || star[3]) return 0U;
    int hi = hex_digit(star[1]);
    int lo = hex_digit(star[2]);
    if (hi < 0 || lo < 0) return 0U;
    uint8_t sum = 0U;
    for (char *p = line + 1; p < star; ++p) sum ^= (uint8_t)*p;
    if (sum != (uint8_t)((hi << 4) | lo)) return 0U;
    *star = '\0';
    return 1U;
}

/* Unlike strtok(), preserve empty NMEA fields so indices remain correct. */
static uint8_t split_csv(char *line, char **fields, uint8_t max_fields)
{
    uint8_t count = 0U;
    if (!max_fields) return 0U;
    fields[count++] = line;
    for (char *p = line; *p; ++p)
    {
        if (*p == ',' && count < max_fields)
        {
            *p = '\0';
            fields[count++] = p + 1;
        }
    }
    return count;
}

static uint8_t nmea_coordinate(const char *s, char hemisphere,
                               uint8_t is_lat, double *out)
{
    if (!s || !*s || !out) return 0U;
    char *end;
    double raw = strtod(s, &end);
    if (end == s || *end || !isfinite(raw) || raw < 0.0) return 0U;
    int deg = (int)(raw / 100.0);
    double minutes = raw - 100.0 * deg;
    int max_deg = is_lat ? 90 : 180;
    if (deg > max_deg || minutes < 0.0 || minutes >= 60.0 ||
        (deg == max_deg && minutes > 0.0)) return 0U;
    if (is_lat) {
        if (hemisphere != 'N' && hemisphere != 'S') return 0U;
    } else {
        if (hemisphere != 'E' && hemisphere != 'W') return 0U;
    }
    *out = deg + minutes / 60.0;
    if (hemisphere == 'S' || hemisphere == 'W') *out = -*out;
    return 1U;
}

static float nonnegative_number(const char *s)
{
    if (!s || !*s) return 0.0f;
    char *end;
    double value = strtod(s, &end);
    if (end == s || *end || !isfinite(value) || value < 0.0 || value > 100000.0)
        return 0.0f;
    return (float)value;
}

static void parse_nmea(char *line)
{
    if (!nmea_checksum_ok(line)) {
        ++gps_data.bad_nmea_count;
        return;
    }
    char *f[22];
    uint8_t count = split_csv(line, f, 22U);
    if (count < 2U || strlen(f[0]) != 6U || f[0][0] != '$') return;

    if (strcmp(f[0] + 3, "RMC") == 0) {
        if (count < 9U || (f[2][0] != 'A' && f[2][0] != 'V')) {
            ++gps_data.bad_nmea_count;
            return;
        }
        /* An RMC sentence was received. A=valid navigation, V=invalid. */
        if (f[2][0] == 'V') {
            gps_data.fix = 0U;
            return;
        }
        double lat, lon;
        if (!nmea_coordinate(f[3], f[4][0], 1U, &lat) ||
            !nmea_coordinate(f[5], f[6][0], 0U, &lon)) {
            ++gps_data.bad_nmea_count;
            gps_data.fix = 0U;
            return;
        }
        gps_data.latitude = lat;
        gps_data.longitude = lon;
        gps_data.speed_kmh = nonnegative_number(f[7]) * 1.852f;
        gps_data.speed_ms = gps_data.speed_kmh / 3.6f;
        gps_data.course = nonnegative_number(f[8]);
        if (gps_data.course >= 360.0f) gps_data.course = 0.0f;
        gps_data.last_update_ms = HAL_GetTick();
        gps_data.fix = 1U;
        ++gps_data.valid_rmc_count;
    }
    else if (strcmp(f[0] + 3, "GGA") == 0 && count >= 8U) {
        /* GGA field 7: satellite count; field 6: quality (0 = no fix). */
        int quality = atoi(f[6]);
        int sats = atoi(f[7]);
        gps_data.satellites = (uint8_t)((quality > 0 && sats >= 0 && sats <= 99)
                                             ? sats : 0);
    }
}

HAL_StatusTypeDef GPS_Init(UART_HandleTypeDef *huart)
{
    if (!huart || !huart->Instance) return HAL_ERROR;
    gps_uart = huart;
    gps_head = gps_tail = gps_line_len = 0U;
    gps_discard_line = 0U;
    gps_need_rearm = 1U;
    memset(&gps_data, 0, sizeof(gps_data));
    HAL_StatusTypeDef ret = HAL_UART_Receive_IT(gps_uart, &gps_rx_byte, 1U);
    if (ret == HAL_OK) gps_need_rearm = 0U;
    return ret;
}

void GPS_RxCallback(uint8_t data)
{
    /* This function can be called from an ISR. No string parsing here. */
    uint16_t next = (uint16_t)((gps_head + 1U) & (GPS_RX_FIFO_SIZE - 1U));
    if (next == gps_tail) {
        ++gps_data.rx_overflow_count;
        return;
    }
    gps_fifo[gps_head] = data;
    __DMB();
    gps_head = next;
}

void GPS_RxCpltCallback(void)
{
    GPS_RxCallback(gps_rx_byte);
    if (gps_uart && HAL_UART_Receive_IT(gps_uart, &gps_rx_byte, 1U) == HAL_OK)
        gps_need_rearm = 0U;
    else
        gps_need_rearm = 1U;
}

void GPS_ErrorCallback(void)
{
    ++gps_data.uart_error_count;
    gps_need_rearm = 1U; /* Re-arm from main; never abort/re-init inside ISR. */
}

void GPS_Process(void)
{
    if (!gps_uart) return;
    /* Error recovery remains in main context, not the UART ISR. */
    if ((gps_need_rearm || gps_uart->RxState == HAL_UART_STATE_READY) &&
        gps_uart->RxState == HAL_UART_STATE_READY)
    {
        if (HAL_UART_Receive_IT(gps_uart, &gps_rx_byte, 1U) == HAL_OK)
            gps_need_rearm = 0U;
    }

    for (uint16_t i = 0U; i < GPS_BYTES_PER_POLL; ++i)
    {
        if (gps_tail == gps_head) break;
        uint8_t ch = gps_fifo[gps_tail];
        gps_tail = (uint16_t)((gps_tail + 1U) & (GPS_RX_FIFO_SIZE - 1U));
        if (ch == '\n') {
            if (!gps_discard_line && gps_line_len) {
                /* CR normally precedes LF; discard it if present. */
                if (gps_line[gps_line_len - 1U] == '\r') --gps_line_len;
                gps_line[gps_line_len] = '\0';
                parse_nmea(gps_line);
            }
            gps_line_len = 0U;
            gps_discard_line = 0U;
        }
        else if (!gps_discard_line) {
            if (gps_line_len + 1U < GPS_NMEA_LINE_SIZE)
                gps_line[gps_line_len++] = (char)ch;
            else {
                gps_discard_line = 1U;
                ++gps_data.rx_overflow_count;
            }
        }
    }
    /* No position may be reported valid if new RMC has stopped arriving. */
    if (gps_data.fix &&
        (uint32_t)(HAL_GetTick() - gps_data.last_update_ms) > GPS_RMC_STALE_MS)
        gps_data.fix = 0U;
}

GPS_Data_t *GPS_GetData(void)
{
    return &gps_data;
}
