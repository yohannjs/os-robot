#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "cake.h"

void* cake_Server(void* param)
{
    int pieces = (int) param;
    
    printf("Yum, I have %d pieces of cake.\n", pieces);
    sleep(1);
    while (pieces > 0)
    {
        sleep(1);
        pieces--;
        printf("Now I have %d\n", pieces);
    }
    pthread_exit(NULL);
    return NULL;
}
