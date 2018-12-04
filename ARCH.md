% Architecture Specification
% Wall-E group
% 29/11-2018


## Modular C code examples
C does not have explicit support for modules, bu we can emulate it with header
files.

```c
/* motor.h */

#define connect motor_connect
#define setAngle motor_setAngle
#define setSpeed motor_setSpeed

extern int connect;
extern int setAngle;
extern int setSpeed;


/* motor.c  */

#include "motor.h"

int connect(int motorNum, int motorPorts[]) {...}
int setAngle(int motorIndex, int angle) {...}
int setSpeed(int motorIndex, int speed) {...}


/* main.c */

#include <stdio.h>
#include "motor.h"

int main() {
    if (motor_connect(3, {1, 2, 3}) == 0) {
        motor_setSpeed(0, 100);
        motor_setAngle(0, 359);
    } else {
        printf("Whoopsiedoopsie\n");
    }
}
```


