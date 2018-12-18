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
// INIT OVER
    // scan_Scan360(samples, speed_scan);
    // scan_WriteSamplesToFile(samples,"template_START.txt");
    sleep(1);
    // GO TO SCAN POSITION SOUTH EAST
    navigation_GoToScanPosition(SOUTH_EAST);
    // sleep(1);
    // scan_Scan360(samples, speed_scan);
    // scan_WriteSamplesToFile(samples,"template_SOUTH_EAST.txt");
    sleep(1);

    // GO TO SCAN POSITION NORTH EAST
    navigation_GoToScanPosition(NORTH_EAST);
    // sleep(1);
    // scan_Scan360(samples, speed_scan);
    // scan_WriteSamplesToFile(samples,"template_NORTH_EAST.txt");
    sleep(1);

    // GO TO SCAN POSITION NORTH WEST
    navigation_GoToScanPosition(NORTH_WEST);
    // sleep(2);
    // scan_Scan360(samples, speed_scan);
    // scan_WriteSamplesToFile(samples,"template_NORTH_WEST.txt");
    sleep(1);
    // GO TO SCAN POSITION SOUTH WEST
    navigation_GoToScanPosition(SOUTH_WEST);
    // sleep(1);
    // scan_Scan360(samples, speed_scan);
    // scan_WriteSamplesToFile(samples,"template_SOUTH_WEST.txt");
    sleep(1);
    navigation_ReturnFromScanPosition();
}