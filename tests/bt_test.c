#include <stdio.h>

#include "bt.h"
#include "utils.h"

int main() {
    printf("Connecting to server...\n");
    if (bt_Connect()) {
        printf("Error! Exiting.\n");
        return 1;
    }
    printf("Connected.\n");
    
    printf("Waiting for start message...\n");
    bt_WaitForStartMessage();

    for (int i=0; i<3; i++){
        printf("Sending score message\n");
        bt_SendScoreMessage(0);
        utils_Sleep( 1000 );
    }
    printf("Sending score message\n");
    bt_SendScoreMessage(1);
    
    printf("Waiting for stop message...\n");
    bt_WaitForStopMessage();
    
    printf("Quitting\n");
    bt_Disconnect();

    return 0;
}
