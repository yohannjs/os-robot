// Include standard C-libraries
#include <stdio.h>
#include <stdint.h>

#include "navigate.h"
#include "scan.h"
#include "claw.h"
#include "detect.h"
#include "utils.h"

// Include project header files



#define STATE_INIT 1
#define STATE_SEARCH 2
#define STATE_GRAB 3
#define STATE_SCORE 4

static int state;
int ball_heading;
int ball_distance;
p prev_point = SOUTH_WEST;
const int start_threshold = 400;
const int corner_threshold = 280;
const int side_threshold = 280;
static int middle_count = 0;


void handler(uint16_t command, uint16_t value)
{
   // Handle commands not dependent on state (communication w/ server)
 //   switch (command)
 //   {
 //       case UPDATE_SCORE_FROM_SERVER:
//            /* code */
//            break;
//    }
    // Handle commands dependent on state

    switch (state)
    {
        case STATE_INIT:
          printf("\nSTATE_INIT\n");
            navigation_Init();
            detect_Init();
            claw_Init();

            // int template_START[360];
            // int template_SOUTH_EAST[360];
            // int template_NORTH_EAST[360];
            // int template_NORTH_WEST[360];
            // int template_SOUTH_WEST[360];

            // scan_LoadSamples("template_START.txt", template_START);
            // scan_LoadSamples("template_SOUTH_EAST", template_SOUTH_EAST);
            // scan_LoadSamples("template_NORTH_EAST", template_NORTH_EAST);
            // scan_LoadSamples("template_NORTH_WEST", template_NORTH_WEST);
            // scan_LoadSamples("template_SOUTH_WEST", template_SOUTH_WEST);

            int samples[360];

            navigation_GoToThrowPosition();
            utils_Sleep(500);
            claw_Throw();
            //send some kind of score message
            claw_TakeBall();
            utils_Sleep(500);
            claw_Throw();
            navigation_ReturnAfterThrow();
            state = STATE_SEARCH;
            break;

        case STATE_SEARCH:
            printf("\nSTATE_SEARCH\n");
            /* code */
            //have some kind of counter that counts defines which positions
            //is to be scanned (if 0, MIDDLE, UP, if 1, LEFT, SIDE etc?)
            switch (prev_point)
            {
                case UNINIT:
                    scan_Scan360(samples);
                    // if(scan_FindBall(samples, template_START, &ball_heading, &ball_distance) == 0) // Should use template here in game
                    scan_FindBall2(samples, start_threshold, &ball_heading, &ball_distance);
                    if(ball_heading == 0 && ball_distance == 0)
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    else
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    }
                    prev_point = MIDDLE;
                    break;

                case MIDDLE:
                    navigation_GoToScanPosition(SOUTH_EAST);
                    printf("Going to SOUTH_EAST\n");
                    printf("Trying to recalibrate now\n");
              //      utils_Sleep(200);
              //      drive_SetHeading(RIGHT);
                //    utils_Sleep(200);
                    navigation_RecalibrateSide();
                    scan_Scan360(samples);
                    scan_FindBall2(samples, side_threshold, &ball_heading, &ball_distance);
                    if(ball_heading == 0 && ball_distance == 0)
                    {
                        printf("Ball not found. \n");
                        middle_count = 4;
                        state = STATE_SEARCH;
                    }
                    else
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    }
                    prev_point = SOUTH_EAST;
                    break;

                case SOUTH_EAST:
                    navigation_GoToScanPosition(NORTH_EAST);
                    printf("Going to NORTH_EAST\n");
                    scan_Scan360(samples);
                    scan_FindBall2(samples, corner_threshold, &ball_heading, &ball_distance);
                    if(ball_heading == 0 && ball_distance == 0)
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    else
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    }
                    prev_point = NORTH_EAST;
                    break;

                case NORTH_EAST:
                    navigation_GoToScanPosition(NORTH_WEST);
                    printf("Going NORTH_WEST\n");
                    scan_Scan360(samples);
                    scan_FindBall2(samples, corner_threshold, &ball_heading, &ball_distance);
                    if(ball_heading == 0 && ball_distance == 0)
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    else
                    {
                        printf("\nFOUND BALL! \n");
                        state = STATE_GRAB;
                    }
                    prev_point = NORTH_WEST;
                    break;

                case NORTH_WEST:
                    navigation_GoToScanPosition(SOUTH_WEST);
                    printf("\nGoing SOUTH_WEST\n");
                    scan_Scan360(samples);
                    scan_FindBall2(samples, side_threshold, &ball_heading, &ball_distance);
                    if(ball_heading == 0 && ball_distance == 0)
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    else
                    {
                        printf("Found ball! \n");
                        state = STATE_GRAB;
                    }
                    prev_point = SOUTH_WEST;
                    break;

                case SOUTH_WEST:
                    navigation_GoToScanPosition(MIDDLE);
                    printf("\nGoing to MIDDLE\n");
                    middle_count = middle_count +1;
                    scan_Scan360(samples);
                    scan_FindBall2(samples, start_threshold, &ball_heading, &ball_distance);
                    if((ball_heading == 0) && (ball_distance == 0))
                    {
                        printf("Ball not found. \n");
                        state = STATE_SEARCH;
                    }
                    else
                    {
                        printf("FOUND BALL! \n");
                        state = STATE_GRAB;
                    }
                    prev_point = MIDDLE;
                    break;

            }
            break;


      case STATE_GRAB:
        navigation_MoveToBall(ball_distance / 10, ball_heading);
        int adjust_distance = detect_GetDistance();
        if (adjust_distance > 250){
              printf("Kob-E probably detected wrong heading, no ball seems to be here\n Going back to search\n");
              navigation_ReturnToScanPosition();
              state = STATE_SEARCH;
              break;
        }
        else{
          navigation_AdjustBallDistance(adjust_distance/10);
        }

        if(claw_TakeBall())
        {
            state = STATE_SCORE;
            navigation_ReturnToScanPosition();
        }
        else
        {
          printf("could not grab ball\n");
          navigation_ReturnToScanPosition();
          scan_Scan360(samples);
          scan_FindBall2(samples, start_threshold, &ball_heading, &ball_distance);
          if((ball_heading == 0) && (ball_distance == 0)) //Try again at searchpoint for lolz
          {
              printf("Ball not found. \n");
              state = STATE_SEARCH;
          }
          else
          {
              printf("FOUND BALL! \n");
              navigation_MoveToBall(ball_distance / 10, ball_heading);
              int adjust_distance = detect_GetDistance();
              navigation_AdjustBallDistance(adjust_distance / 10);
              if(claw_TakeBall())
              {
                  state = STATE_SCORE;
                  navigation_ReturnToScanPosition();
              }
              else
              {
                  navigation_ReturnToScanPosition();
                  state = STATE_SEARCH;
              }
          }
        }
        break;

        case STATE_SCORE:
            /* code */
            printf("\nSTATE_SCORE\n");
            navigation_ReturnFromScanPosition();
            // NEED TO CHECK BATTERY LEVEL HERE
            printf("Recalibrating\n");
            navigation_RecalibrateBeforeScore();
            //navigation_GoToThrowPosition();
            utils_Sleep(500);
            printf("Scoring\n");
            claw_Throw();
            //send some kind of score message
            printf("Returning after throw\n");
            navigation_ReturnAfterThrow();
            state = STATE_SEARCH;
            if (middle_count < 3){
              prev_point = SOUTH_WEST;
            }
            break;
    }
}

int main()
{
    printf("Kob-e\n");
    state = STATE_INIT;
    uint16_t command;
    int16_t value;
    for(;;)
    {
        handler(command, value);
    }
    return 0;
}
