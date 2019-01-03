#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "navigate.h"
#include "claw.h"
#include "scan.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("No arguments given. Exiting...\n");
        return 1;
    }
    claw_Init();
    drive_Init();
    int test = (int) argv[1][0] - 48;
    switch(test)
    {
        case 1:
            printf("Running drop test...\n");

            // Move to basket wall
            navigation_MoveToDropPosition();
            sleep(7);
            // Drop ball
            claw_Drop();
            sleep(3);
            claw_Reset();
            break;
        case 2:
            printf("Running short throw test...\n");
            // Move to front area tape

            // Move over it

            // Throw ball with reduced strength

            break;
        case 3:
            printf("Running long throw test...\n");

            // Move to front area tape
            navigation_GoToShootingPosition();
            sleep(3);
            // Throw ball
            claw_Throw();
            printf("NYYAHH!\n");

            break;
        case 4:
            printf("Running easy find test...\n");

            // Perform scan on our side of the stadium
            // (ball WILL be detected)
            int* ball_heading;
            int* ball_distance;
            navigation_GoToScanPosition(MIDDLE, UP);
            sleep(2);
            scan_Scan(&ball_heading, &ball_distance;);
            sleep(4);
            // Move to ball
            navigation_MoveToBall(ball_heading, ball_distance);
            sleep(4);
            // Pick up ball
            if(claw_Grab()){
              printf("could not grab the ball :( \n)");
            }
            sleep(1);
            //return to start
            navigation_ReturnToScanPosition();
            sleep(4);
            navigation_ReturnFromScanPosition();
            break;
        case 5:
            printf("Running hard find test...\n");

            // Perform scan on our side of the stadium

            // If ball is not found, move to alternative scanning position and
            // repeat scan, repeat until found

            // When ball is detected at our side of the stadium, move to ball
            // and pick it up

            break;
        case 6:
            printf("Running bluetooth test...\n");

            // Connect to bt server

            // Wait some seconds

            // Send score message

            break;
        default:
            printf("Invalid test number. Exiting...\n");
            return 1;
    }
    printf("Test finished.\n");

    return 0;
}
