#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// #include "claw.h"
// #include "detect.h"
// #include "drive.h"
// #include "scan.h"
#include "navigate.h"

// In this module the robot must start in the start route
// It then drives to the four scanning positions of the field.

// int speed = 40;
// int degrees = 359;
// FILE* f;
// int NUM_SAMPLES;
// int heading_ball;
// int distance_ball;

// int samples[360];
// int speed_scan = 3;

int main()
{
    navigation_Init();
    // detect_Init();
    // claw_Init();

// INIT OVER

// OTHER TESTS

    // GO TO SCAN POSITION NORTH EAST
    navigation_GoToScanPosition(SOUTH_EAST);

    // GO TO SCAN POSITION NORTH EAST
    navigation_GoToScanPosition(NORTH_EAST);

    // GO TO SCAN POSITION NORTH WEST
    navigation_GoToScanPosition(NORTH_WEST);

    // GO TO SCAN POSITION SOUTH WEST
    navigation_GoToScanPosition(SOUTH_WEST);

    // GO BACK TO MIDDLE
    navigation_ReturnFromScanPosition();
}