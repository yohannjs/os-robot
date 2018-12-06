#include "colorsensor.h"
#include "../lib/ev3.h"
#include "../lib/ev3_sensor.h"

static int32_t seqnum;

uint8_t colorsensor_init(void) 
{
    if (ev3_init() == -1)
    {
        return 1;
    {
    if (ev3_search_sensor(LEGO_EV3_COLOR, &seqnum, 0)) 
    {
        set_sensor_mode(seqnum, "COL-COLOR");
    }
    else
    {
        return 2;
    }
    return 0;
}

bool colorsensor_darkness(void) 
{
    float value;
    get_sensor_value0(seqnum, &value) 
    if (value == 1) 
    {
        return true;
    }
    return false;
}
