#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_sensor.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )

#define COLOR_COUNT 8

static uint8_t sn_color;
static uint8_t sn_sonar;

int detect_Init(void)
{
    if (ev3_init() == -1) return 1;
    if (ev3_sensor_init() == -1) return 1;

    if (ev3_search_sensor(LEGO_EV3_COLOR, &sn_color, 0))
    {
        printf("[detect] Color sensor found\n");
    	set_sensor_mode(sn_color, "COL-COLOR");
    }
    else
    {
        printf("[detect] [ERROR] Color sensor not found\n");
        return 1;
    }

    if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar, 0))
    {
        printf("[detect] Distance sensor found\n");
    }
    else
    {
        printf("[detect] [ERROR] Distance sensor not found\n");
        return 1;
    }
    return 0;
}

int detect_GetDistance(void)
{
    float value;
    if (!get_sensor_value0(sn_sonar, &value))
    {
        printf("[detect] [ERROR] Distance sensor not responding\n");
        value = 0;
    }
    return value;
}

bool detect_OnLine(void)
{
    int value;
    bool isBlack = false;
    if ( !get_sensor_value( 0, sn_color, &value ) || ( value < 0 ) || ( value >= COLOR_COUNT ))
    {
        printf("[detect] [ERROR] Color sensor not responding\n");
    }
    else
    {
        if(value == 1)
        {
            isBlack = true;
        }
    }
    return isBlack;
}
