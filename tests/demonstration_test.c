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
    
    int test = (int) argv[1][0] - 48;
    switch(test)
    {
        case 1:
            printf("Running drop test...\n");
            
            // Move to basket wall
            
            // Drop ball
            
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
            
            // Throw ball
            printf("NYYAHH!\n");
            
            break;
        case 4:
            printf("Running easy find test...\n");
            
            // Perform scan on our side of the stadium
            // (ball WILL be detected)
            
            // Move to ball
            
            // Pick up ball
            
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
