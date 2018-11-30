#include <stdio.h>

#include "motors.h"

int main()
{
    //int ports[] = {1, 2};
    //motors_connect(2, ports);
    motors_setSpeed(0, 127);
    motors_setAngle(0, 255);
    
    printf("C er bra.\n");    
    return 0;
}
