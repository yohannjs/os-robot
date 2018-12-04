% Architecture Specification
% Kob-E group
% 29/11-2018

# Robot use cases
Our robot shall execute the following steps (or use cases):
1. Register to contest on the server
2. Aim for the basket
3. Throw ball
4. Signal a goal to the server
5. Find a new ball
6. Pick up the ball
7. Return to the starting location
8. _Go to step 2_

## Register to contest on the server
For this we need only the bluetooth system.

## Aim for the basket
Here we need to position the robot correctly. Since the basket is further away 
than 30 cm, we cannot use the sonar (reliably), we should then probably use
only the color detection sensor to detect different colors on the floor.

# Project strucure
Our project will consist of 3 parts:

## Business
The main logic of our system, in our case it consists mostly of a state machine.

## Use Cases
The high level actions our system shall be able to perform. The same use cases
as described in the previous section. 

## Adapters
The "low level" interface with the subsystems of our system. Like the navigation
subsystem that interfaces with wheel motors and compass, or the game system that
uses the bluetooth communication library.

# Folder structure
```
src/
    lib/
    business/
    usecases/
    adapters/
    main.c
    Makefile
```

`main.c` is the most dirty of our modules, it knows about all the parts of our 
system and is responsible for connect all of our modules toghether. Therefore 
it is placed at the outside of the other folders.

# Modular C code examples
C does not have explicit support for modules, but we can emulate it with header
files.

```c
/* motors.h */

extern int motors_connect(int motorNum, int motorPorts[]);
extern void motors_setAngle(int motorIndex, int angle);
extern void motors_setSpeed(int motorIndex, int speed);


/* motors.c  */

#include "motors.h"

int motors_connect(int motorNum, int motorPorts[]) 
{
    // Implementation...
}

int motors_setAngle(int motorIndex, int angle) 
{
    // Implementation...
}

int motors_setSpeed(int motorIndex, int speed) 
{
    // Implementation...
}


/* main.c */

#include <stdio.h>
#include "motors.h"

int main() {
    if (motors_connect(3, {1, 2, 3}) == 0) {
        motors_setSpeed(0, 100);
        motors_setAngle(0, 359);
    } else {
        printf("Whoopsiedoopsie\n");
    }
}
```


