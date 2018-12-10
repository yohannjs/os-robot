#include <stdio.h>
//#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "adapters/cake.h"

int main()
{
    pthread_t thread;
    
    int ja = 10;

    printf("I am making a thread.\n");
    
    sleep(2);
    
    //printf("lol\n");
    
    if (pthread_create(&thread, NULL, cake_Server, (void*) ja))
    {
        printf("Could not create thread");
        return 1;
    }
    
    sleep(3);
    printf("dats cool\n");

    pthread_exit(NULL);
    return 0;
}
