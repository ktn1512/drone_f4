/* GPS: parse $GNRMC, tọa độ thập phân, tốc độ km/h, m/s và course. */
#include "gps.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define GPS_BUFFER_SIZE 128

static UART_HandleTypeDef *gps_uart;

static char line_buffer[GPS_BUFFER_SIZE];

static uint16_t line_index = 0;

static GPS_Data_t gps_data;

/* Chuyển NMEA ddmm.mmmm thành độ thập phân: degrees + minutes/60. */
static double NMEA_To_Degree(const char *str)
{

    double raw = atof(str);

    int degree = (int)(raw / 100);

    double minute = raw - (degree * 100);

    return degree + minute / 60.0;
}

HAL_StatusTypeDef GPS_Init(UART_HandleTypeDef *huart)
{

    gps_uart = huart;

    memset(&gps_data, 0, sizeof(gps_data));

    return HAL_OK;
}

/* RMC: trường 2 fix, 3-6 tọa độ, 7 knot, 8 course. */
static void GPS_ParseRMC(char *sentence)
{

    char *token;

    uint8_t field = 0;

    char lat_str[16] = {0};

    char lon_str[16] = {0};

    char lat_dir = 'N';

    char lon_dir = 'E';

    token = strtok(sentence, ",");

    while (token != NULL)
    {
        switch (field)
        {
        case 2:

            gps_data.fix = (token[0] == 'A');

            break;

        case 3:

            strcpy(lat_str, token);

            break;

        case 4:

            lat_dir = token[0];

            break;

        case 5:

            strcpy(lon_str, token);

            break;

        case 6:

            lon_dir = token[0];

            break;

        case 7:

            gps_data.speed_kmh =
                atof(token) * 1.852f /* 1 knot = 1,852 km/h */;

            gps_data.speed_ms =
                gps_data.speed_kmh / 3.6f;

            break;

        case 8:

            gps_data.course = atof(token);

            break;
        }

        token = strtok(NULL, ",");

        field++;
    }

    gps_data.latitude =
        NMEA_To_Degree(lat_str);

    gps_data.longitude =
        NMEA_To_Degree(lon_str);

    if (lat_dir == 'S')
    {
        gps_data.latitude *= -1.0;
    }

    if (lon_dir == 'W')
    {
        gps_data.longitude *= -1.0;
    }
}

void GPS_RxCallback(uint8_t data)
{

    if (data == '\n')
    {

        line_buffer[line_index] = 0;

        GPS_Process();

        line_index = 0;
    }
    else
    {

        if (line_index < GPS_BUFFER_SIZE - 1)
        {

            line_buffer[line_index++] = data;
        }
    }
}

void GPS_Process(void)
{

    if (strncmp(line_buffer, "$GNRMC", 6) == 0)
    {

        char temp[GPS_BUFFER_SIZE];

        strcpy(temp, line_buffer);

        GPS_ParseRMC(temp);
    }
}

GPS_Data_t *GPS_GetData(void)
{
    return &gps_data;
}
