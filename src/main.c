// Include standard C-libraries
#include <stdio.h>

// Include project header files 

#define Sleep( msec ) usleep(( msec ) * 1000 )

#define STATE_SEARCH_BALL 1 
#define STATE_BALL_GRAB 2
#define STATE_SEARCH_GOAL 3
#define STATE_BALL_SCORE 4

int state;

void handler(uint16_t command, int16_t value)
{
    // Handle commands not dependent on state (communication w/ server)
    switch (command)
    {
        case INCREASE_SCORE:
            /* code */
            break;
        case DECREASE_SCORE:
            /* code */
            break;
    }
    // Handle commands dependent on state
    
    switch (state)
    {
        case STATE_SEARCH_BALL:
            /* code */
            state = STATE_BALL_GRAB;
            break;
        
        case STATE_BALL_GRAB:
            /* code */
            state = STATE_SEARCH_GOAL;
            break;
        
        case STATE_SEARCH_GOAL:
            /* code */
            state = STATE_BALL_SCORE;
            break;
        
        case STATE_BALL_SCORE:
            /* code */
            state = STATE_SEARCH_BALL;
            break;
    }
}

int main()
{
    printf("Kob-e\n");
    uint16_t command;
	int16_t value;
	for(;;){
		event_handler(command, value);
	}
    return 0;
}
