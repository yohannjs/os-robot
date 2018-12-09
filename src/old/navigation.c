#include "navigation.h"
#include "../interfaces/motors.h"
#include "../interfaces/colorsensor.h"

#include <unistd.h>

static int rightIndex, leftIndex;

int navigation_init(int rightMotorIndex, int leftMotorIndex)
{
    // Check if motor module is initialized    
    
    // Check if colorsensor is initialized
    
    rightIndex = rightMotorIndex;
    leftIndex = leftMotorIndex;

    return 0;
}

void navigation_moveUntilLine(void)
{
    motors_setSpeed(rightIndex, 100);
    motors_setSpeed(leftIndex, 100);
    
    while (!colorsensor_darkness())
    {
        usleep(10000); // Release cpu control for ~10ms
    }
    
    motors_setSpeed(rightIndex, 0);
    motors_setSpeed(leftIndex, 0);
}




