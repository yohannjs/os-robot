#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "claw.h"
#include "detect.h"
#include "drive.h"
#include "scan.h"
#include "navigate.h"

// In this module the robot mus start in the start route
// It then drives to the four scanning positions of the field and does a scan.

int speed = 40;
int degrees = 359;
FILE* f;
int NUM_SAMPLES;
int heading_ball;
int distance_ball;

int samples[360];
int speed_scan = 3;

int main()
{
    navigation_Init();
    detect_Init();
    claw_Init();

    // drive_SetHeadingY(UP);
    // drive_SetHeadingY(DOWN);
    // drive_SetHeadingY(LEFT);
    // drive_SetHeadingY(RIGHT);
    // drive_SetHeadingY(LEFT_DIAGONAL);
    // drive_SetHeadingY(RIGHT_DIAGONAL);
    // drive_SetHeadingY(UP);
// INIT OVER
    // drive_SetHeading(RIGHT);
    // drive_SetHeading(LEFT);
    // drive_SetHeading(RIGHT_DIAGONAL);
    // drive_SetHeading(LEFT_DIAGONAL);

// OTHER TESTS
    // // GO TO SCAN POSITION SOUTH EAST
    // navigation_GoToScanPosition(SOUTH_EAST);
    // navigation_ReturnFromScanPosition();

    // // GO TO SCAN POSITION NORTH EAST
    // navigation_GoToScanPosition(NORTH_EAST);
    // navigation_ReturnFromScanPosition();

    // // GO TO SCAN POSITION NORTH WEST
    // navigation_GoToScanPosition(NORTH_WEST);
    // navigation_ReturnFromScanPosition();

    // // GO TO SCAN POSITION SOUTH WEST
    // navigation_GoToScanPosition(SOUTH_WEST);

    // // GO BACK TO MIDDLE
    // navigation_ReturnFromScanPosition();

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