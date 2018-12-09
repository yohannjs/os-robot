#include "sonar.h"
#include "../lib/ev3.h"
#include "../lib/ev3_sensor.h"

static int seqnum;

int sonar_init(void)
{
    if (ev3_init() == -1)
    {
        return 1;
    }
    if (!ev3_search_sensor(LEGO_EV3_US, &seqnum, 0)) 
    {
        return 2;
    }
    return 0;
}

int sonar_getDistance(void)
{
    int value;
    get_sensor_value0(seqnum, &value);
    return value;
}
