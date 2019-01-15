#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "claw.h"
#include "detect.h"
#include "drive.h"
#include "scan.h"
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

int main(int argc, char **argv)
{
    navigation_Init();
    detect_Init();
    claw_Init();
    int samples[360];
    // int template[360];
    int heading;
    int distance;
    int threshold = 200;
    
// INIT OVER
    scan_Scan360( samples, 3 );
    printf("Done with scan, moving to file \n");
    // printf(argv[1]);
    scan_FindBall2(samples, threshold, &heading, &distance);
    scan_WriteSamplesToFile( samples, argv[1] );
    printf("Heading ball: %d \n", heading);
    printf("Distance ball: %d \n", distance);
    navigation_MoveToBall(distance / 10, heading);
    int adjust = detect_GetDistance();
    navigation_AdjustBallDistance(adjust / 10);
    claw_TakeBall();

// OTHER TESTS


}