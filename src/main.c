// // Include standard C-libraries
// #include <stdio.h>
// #include "navigate.h"
// #include "scan.h"

// // Include project header files

// #define Sleep( msec ) usleep(( msec ) * 1000 )

// #define STATE_SEARCH_BALL 1
// #define STATE_BALL_GRAB 2
// #define STATE_SEARCH_GOAL 3
// #define STATE_BALL_SCORE 4

// static int state;
// static int* ball_heading;
// static int* ball_distance;

// void handler(uint16_t command, uint16_t value)
// {
//     // Handle commands not dependent on state (communication w/ server)
//     switch (command)
//     {
//         case INCREASE_SCORE:
//             /* code */
//             break;
//         case DECREASE_SCORE:
//             /* code */
//             break;
//     }
//     // Handle commands dependent on state

//     switch (state)
//     {
//         case STATE_SEARCH_BALL:
//             /* code */

//             //have some kind of counter that counts defines which positions
//             //is to be scanned (if 0, MIDDLE, UP, if 1, LEFT, SIDE etc?)
//             navigation_GoToScanPosition(MIDDLE, UP);
//             if (detect_Scan(&ball_distance, &ball_heading)){
//               printf("No ball found\n");
//             }
//             state = STATE_BALL_GRAB;
//             break;

//         case STATE_BALL_GRAB:
//             /* code */
//             navigation_MoveToBall(ball_distance, ball_heading);
//             if(claw_Grab()){
//               printf("could not grab ball\n")
//             }

//             state = STATE_SEARCH_GOAL;
//             break;

//         case STATE_SEARCH_GOAL:
//             /* code */
//             navigation_ReturnToScanPosition();
//             navigation_ReturnFromScanPosition();
//             navigation_GoToShootingPosition();
//             state = STATE_BALL_SCORE;
//             break;

//         case STATE_BALL_SCORE:
//             /* code */
//             claw_Throw();
//             //send some kind of score message
//             navigation_ReturnAfterThrow();
//             state = STATE_SEARCH_BALL;
//             break;
//     }
// }

// int main()
// {
//   printf("Kob-e\n");
//   uint16_t command;
// 	int16_t value;
// 	for(;;){
// 		handler(command, value);
// 	}
//     return 0;
// }
