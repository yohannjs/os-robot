#include "motors.h"

#include <stdlib.h>
#include <unistd.h>

static uint8_t motors_number;
static uint8_t* motors_ports;
static uint8_t* motors_seqnums;
static int32_t* motors_maxSpeed;

uint8_t motors_init(uint8_t number, uint8_t* ports)
{
    // Set module veriables
    motors_number = number;
    motors_ports = (uint8_t*) malloc(number * sizeof(uint8_t));
    motors_seqnums = (uint8_t*) malloc(number * sizeof(uint8_t)); 
    motors_maxSpeed = (int32_t*) malloc(number * sizeof(uint32_t));

    // Init parameters
    uint16_t rampUpSpeed = 5;
    uint16_t rampDownSpeed = 5;

    // Initialize ev3 motor module
    uint16_t i;
    for (i = 0; i < 5; i++) 
    {
        if (ev3_tachos_init() < 1)
        {
            break;
        }
        else
        {
            return 1;
        }
        sleep(1000);
    }
    
    // Check that each individual motor is present and configure them
    for (i = 0; i < number; i++) 
    {
        if (ev3_search_tacho_plugged_in(motors_ports[i], 0, &motors_seqnums[i], 0))
        {
            set_tacho_stop_action_inx(motors_seqnums[i], TACHO_HOLD);
            set_tacho_ramp_up_sp(motors_seqnums[i], rampUpSpeed);
            set_tacho_ramp_down_sp(motors_seqnums[i], rampDownSpeed);
            get_tacho_max_speed(motors_seqnums[i], &motors_maxSpeed[i]);
        }
        else
        {
            return 2;
        }
    }

    return 0;
}

void motors_setSpeed(uint8_t motorIndex, int8_t speed)
{
    if (speed == 0) 
    {
        set_tacho_speed_sp(motors_seqnums[motorIndex], 0);
        set_tacho_command_inx(motors_seqnums[motorIndex], TACHO_STOP);
    }
    else 
    {
        set_tacho_speed_sp(motors_seqnums[motorIndex], speed * motors_maxSpeed[i] / 128); 
        set_tacho_command_inx(motors_seqnums[motorIndex], TACHO_RUN_FOREVER);
    }
}
