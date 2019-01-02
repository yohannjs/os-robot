#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "claw.h"
#include "detect.h"
#include "drive.h"
#include "scan.h"
#include "navigate.h"

int speed = 40;
int degrees = 359;
FILE* f;
int NUM_SAMPLES;
int heading_ball;
int distance_ball;

int speed_scan = 3;

int main()
{
    int samples[360];
    navigation_Init();
    detect_Init();
    claw_Init();
// INIT OVER
    scan_Scan360(samples, speed_scan);
    scan_WriteSamplesToFile(samples,"template_START.txt");
    sleep(1);
    // GO TO SCAN POSITION SOUTH EAST
    navigation_GoToScanPosition(MID_SIDE, RIGHT);
    sleep(1);
    scan_Scan360(samples, speed_scan);
    scan_WriteSamplesToFile(samples,"template_SOUTH_EAST.txt");
    sleep(1);

    // GO TO SCAN POSITION NORTH EAST
    navigation_GoToScanPosition(NORTH_SOUTH, UP);
    sleep(1);
    scan_Scan360(samples, speed_scan);
    scan_WriteSamplesToFile(samples,"template_NORTH_EAST.txt");
    sleep(1);

    // GO TO SCAN POSITION NORTH WEST
    navigation_GoToScanPosition(EAST_WEST, LEFT);
    sleep(2);
    scan_Scan360(samples, speed_scan);
    scan_WriteSamplesToFile(samples,"template_NORTH_WEST.txt");
    sleep(1);
    // GO TO SCAN POSITION SOUTH WEST
    navigation_GoToScanPosition(NORTH_SOUTH, DOWN);
    sleep(1);
    scan_Scan360(samples, speed_scan);
    scan_WriteSamplesToFile(samples,"template_SOUTH_WEST.txt");
    sleep(1);

    navigation_GoToScanPosition(MID_SIDE, RIGHT);
    sleep(1);

    drive_SetHeading(0);

    // navigation_ReturnFromScanPosition();
}
