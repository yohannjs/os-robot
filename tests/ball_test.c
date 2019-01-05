#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "claw.h"
#include "drive.h"
#include "detect.h"
#include "scan.h"
#include "navigate.h"


int speed = 40;
int degrees = 355;
FILE* f;
int NUM_SAMPLES;
int heading_ball;
int distance_ball;

int main()
{
    drive_Init();
    detect_Init();
    claw_Init();
    navigation_GoToScanPosition(MIDDLE,UP);
    sleep(2);
    NUM_SAMPLES = scan_TurnRightScan(degrees, speed);
    scan_FindBallHeading(NUM_SAMPLES, &heading_ball, &distance_ball);
    navigation_MoveToBall(distance_ball, heading_ball);
    sleep(1);
    if(!claw_TakeBall()){
        printf("[Claw] ERROR: Unable to pick up ball. \n");
    } else {
        sleep(1);
        printf("[Claw] Picked up ball, SprutNais!");
    }
    navigation_ReturnToScanPosition();
    return 0;
}
