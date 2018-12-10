#include <stdio.h>
//#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "adapters/cake.h"

int main()
{

    if (cake_Init())
        printf("Something went wrong creating the cake mqs!\n");
    else
        printf("Cake mqs created successfully\n");

    printf("I am making a thread.\n");
    
    sleep(2);
    
    pthread_t thread;
    if (pthread_create(&thread, NULL, cake_Server, (void*) 10))
    {
        printf("Could not create thread");
        return 1;
    }
    
    sleep(5);
    cake_Stop(); 

    pthread_exit(NULL);
    return 0;
}
