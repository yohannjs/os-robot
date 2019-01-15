// Include standard C-libraries
#include <stdio.h>
#include <stdint.h>

#include "navigate.h"
#include "scan.h"
#include "claw.h"
#include "detect.h"

// Include project header files

#define Sleep( msec ) usleep(( msec ) * 1000 )

#define STATE_INIT 1
#define STATE_SEARCH 2
#define STATE_GRAB 3
#define STATE_SCORE 4

static int state;
static int* ball_heading;
static int* ball_distance;
p prev_point = SOUTH_WEST;

void handler(uint16_t command, uint16_t value)
{
    // Handle commands not dependent on state (communication w/ server)
    switch (command)
    {
        case UPDATE_SCORE_FROM_SERVER:
            /* code */
            break;
    }
    // Handle commands dependent on state

    switch (state)
    {
        case STATE_INIT:
            navigation_Init();
            detect_Init();
            claw_Init();

            int template_START[360];
            int template_SOUTH_EAST[360];
            int template_NORTH_EAST[360];
            int template_NORTH_WEST[360];
            int template_SOUTH_WEST[360];

            scan_LoadSamples("template_START.txt", template_START);
            scan_LoadSamples("template_SOUTH_EAST", template_SOUTH_EAST);
            scan_LoadSamples("template_NORTH_EAST", template_NORTH_EAST);
            scan_LoadSamples("template_NORTH_WEST", template_NORTH_WEST);
            scan_LoadSamples("template_SOUTH_WEST", template_SOUTH_WEST);

            int samples[360];

            navigation_GoToThrowPosition();
            claw_Throw();
            //send some kind of score message
            claw_Grab();
            claw_Throw();
            navigation_ReturnAfterThrow();
            state = STATE_SEARCH;
            break;

        case STATE_SEARCH:
            /* code */
            //have some kind of counter that counts defines which positions
            //is to be scanned (if 0, MIDDLE, UP, if 1, LEFT, SIDE etc?)
            switch (prev_point)
            {
                case UNINIT:
                    scan_Scan360(samples, 3);
                    if(scan_FindBall(samples, template_START, &ball_heading, &ball_distance) == 0)
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    } 
                    else 
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    prev_point = MIDDLE;
                    break;

                case MIDDLE:
                    navigation_GoToScanPosition(SOUTH_EAST);
                    scan_Scan360(samples, 3);
                    if(scan_FindBall2(samples, 30, &ball_heading, &ball_distance)
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    } 
                    else 
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    prev_point = SOUTH_EAST;
                    break;

                case SOUTH_EAST:
                    navigation_GoToScanPosition(NORTH_EAST);
                    scan_Scan360(samples, 3);
                    if(scan_FindBall2(samples, 20, &ball_heading, &ball_distance) == 0)
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    } 
                    else 
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    prev_point = NORTH_EAST;
                    break;

                case NORTH_EAST:
                    navigation_GoToScanPosition(NORTH_WEST);
                    scan_Scan360(samples, 3);
                    if(scan_FindBall2(samples, 20, &ball_heading, &ball_distance) == 0)
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    } 
                    else 
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    prev_point = NORTH_WEST;
                    break;

                case NORTH_WEST:
                    navigation_GoToScanPosition(SOUTH_WEST);
                    scan_Scan360(samples, 3);
                    if(scan_FindBall2(samples, 20, &ball_heading, &ball_distance) == 0)
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    } 
                    else 
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    prev_point = SOUTH_WEST;
                    break;

                case SOUTH_WEST:
                    navigation_GoToScanPosition(MIDDLE);
                    scan_Scan360(samples, 3);
                    if(scan_FindBall2(samples, 20, &ball_heading, &ball_distance) == 0)
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    } 
                    else 
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    prev_point = MIDDLE;
                    break;

            }
            break;

        case STATE_GRAB:
            /* code */
            navigation_MoveToBall(*ball_distance, *ball_heading);
            int adjust_distance = detect_GetDistance();
            navigation_AdjustBallDistance(adjust_distance);
            if(claw_TakeBall())
            {
                printf("could not grab ball\n");
                navigation_ReturnToScanPosition();
                state = STATE_SEARCH;
            } 
            else
            {
                state = STATE_SCORE;
            }
            break;

        case STATE_SCORE:
            /* code */
            navigation_ReturnFromScanPosition();
            // NEED TO CHECK BATTERY LEVEL HERE
            navigation_GoToThrowPosition();
            claw_Throw();
            //send some kind of score message
            navigation_ReturnAfterThrow();
            state = STATE_SEARCH;
            break;
    }
}

int main()
{
    printf("Kob-e\n");
    uint16_t command;
    int16_t value;
    for(;;)
    {
        handler(command, value);
    }
    return 0;
}
