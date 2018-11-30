#include "motors.h"

static int num;
static int* ports;

int motors_connect(int motorNum, int* motorPorts)
{
    num = motorNum; 
    for (int i=0; i<num; i++) {
        ports[i] = motorPorts[i];
    }
    return num;
}

void motors_setSpeed(int motorIndex, int speed)
{
    // lol
}

void motors_setAngle(int motorIndex, int angle)
{
    // lol
}
