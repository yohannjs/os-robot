#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "claw.h"
#include "detect.h"
#include "scan.h"
#include "navigate.h"
#include "drive.h"

int speed = 40;
int degrees = 359;
FILE* f;
int NUM_SAMPLES;
int heading_ball = 0;
int distance_ball = 0;
int speed_scan = 4;



int main(int argc, char **argv)
{
    // INIT
    navigation_Init();
    detect_Init();
    claw_Init();

    // INITIALIZE TEMPLATES AND SAMPLES FOR SCAN
    int template_START[360];
    // int template_SOUTH_EAST[360];
    // int template_NORTH_EAST[360];
    // int template_NORTH_WEST[360];
    // int template_SOUTH_WEST[360];

    int samples_START[360];
    // int samples_SOUTH_EAST[360];
    // int samples_NORTH_EAST[360];
    // int samples_NORTH_WEST[360];
    // int samples_SOUTH_WEST[360];

    // LOAD TEMPLATES
    scan_LoadSamples("template_START.txt", template_START);
    // scan_LoadSamples("template-making/template_SOUTH_EAST", template_SOUTH_EAST);
    // scan_LoadSamples("template-making/template_NORTH_EAST", template_NORTH_EAST);
    // scan_LoadSamples("template-making/template_NORTH_WEST", template_NORTH_WEST);
    // scan_LoadSamples("template-making/template_SOUTH_WEST", template_SOUTH_WEST);

    // LOOK FOR BALL AT POSITION START

    
    if (argc == 1) 
    {
        scan_Scan360(samples_START, speed_scan);
        sleep(1);
        for (int i = 0; i < 360; i++)
        {
            printf("samples_START[%d] = %d, template_START[%d] = %d \n", i, samples_START[i], i, template_START[i]);
        }
    }
    else if (argc == 2)
    {
        scan_Scan360(samples_START, speed_scan);
        sleep(1);
        if(scan_FindBall(samples_START, template_START, &heading_ball, &distance_ball) == 0)
        {
            printf("FOUND BALL! \n");
            navigation_MoveToBall(distance_ball / 10, heading_ball);
            if(claw_TakeBall() != 1)
            {
                printf("Wasn't able to pick up ball.. \n");
            }
            // return 0;
        } else 
        {
            printf("Ball not found. \n");
        }
    }
    else if (argc == 3)
    {
        NUM_SAMPLES = scan_TurnRightScan(355, 40);
        scan_FindBallHeading(NUM_SAMPLES, &heading_ball, &distance_ball);
        navigation_MoveToBall(distance_ball / 10, heading_ball);
        if(claw_TakeBall() != 1)
        {
            printf("Wasn't able to pick up ball.. \n");
        }
    }
    /*
    // LOOK FOR BALL AT POSITION SOUTH EAST
    navigation_GoToScanPosition(SIDE, RIGHT);
    scan_Scan360(samples_SOUTH_EAST, speed_scan);
    sleep(1);
    if(scan_FindBall(samples_SOUTH_EAST, template_SOUTH_EAST, heading_ball, distance_ball) == 0)
    {
        printf("FOUND BALL! \n");
        navigation_MoveToBall(distance_ball, heading_ball);
        if(claw_TakeBall() != 1)
        {
            printf("Wasn't able to pick up ball.. \n");
        }
        return 0;
    }

    // LOOK FOR BALL AT POSITION NORTH EAST
    navigation_GoToScanPosition(SIDE, UP);
    scan_Scan360(samples_NORTH_EAST, speed_scan);
    sleep(1);
    if(scan_FindBall(samples_NORTH_EAST, template_NORTH_EAST, heading_ball, distance_ball) == 0)
    {
        printf("FOUND BALL! \n");
        navigation_MoveToBall(distance_ball, heading_ball);
        if(claw_TakeBall() != 1)
        {
            printf("Wasn't able to pick up ball.. \n");
        }
        return 0;
    }

    // LOOK FOR BALL AT POSITION NORTH WEST
    navigation_GoToScanPosition(2*SIDE, LEFT);
    scan_Scan360(samples_NORTH_WEST, speed_scan);
    sleep(1);
    if(scan_FindBall(samples_NORTH_WEST, template_NORTH_WEST, heading_ball, distance_ball) == 0)
    {
        printf("FOUND BALL! \n");
        navigation_MoveToBall(distance_ball, heading_ball);
        if(claw_TakeBall() != 1)
        {
            printf("Wasn't able to pick up ball.. \n");
        }
        return 0;
    }

    // LOOK FOR BALL AT POSITION SOUTH WEST
    navigation_GoToScanPosition(SIDE, DOWN);
    scan_Scan360(samples_SOUTH_WEST, speed_scan);
    sleep(1);
    if(scan_FindBall(samples_SOUTH_WEST, template_SOUTH_WEST, heading_ball, distance_ball) == 0)
    {
        printf("FOUND BALL! \n");
        navigation_MoveToBall(distance_ball, heading_ball);
        if(claw_TakeBall() != 1)
        {
            printf("Wasn't able to pick up ball.. \n");
        }
        return 0;
    }

    navigation_GoToScanPosition(SIDE, RIGHT);
    */
    drive_SetHeading(0);

}