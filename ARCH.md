% Architecture Specification
% Wall-E group
% 29/11-2018

# Basics
To write the best possible code, we want to use Test Driven Development (TDD).
This means writing the tests for our software before we write the code. We'll 
write unit tests, intregration tests and end-to-end tests. 

## Unit tests
Tests for individual functions.

## Integration tests
Tests for module-on-module action. How modules works together.

## End-to-end tests
Test of the entire system. Different scenarios the robot can encounter.

In addition to help 
us write good code, it will also force us to modularize our source code.
Modularized code will allow us to switch out modules with "mock modules",
modules we have written that mocks the behaviour of other modules. This makes
it possible to test the entire system locally in our test environment without
connecting to the robot at all. Sensors and motors can be mocked, and the
rest of the system will be oblivious to it, as long as it behaves in the same
manner as the actual module. To accomplish this, we need modules with clear, 
well defined interfaces.

## Modular C code examples
C does not have explicit support for modules, bu we can emulate it with header
files.


´´´c
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
´´´


