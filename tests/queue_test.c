#include <stdio.h>
#include <mqueue.h>

#include "queue.h"

int main(void)
{
    mqd_t q1;
    mqd_t q2;
    
    printf("Creating queue /q1\n");
    if (queue_Create("/q1", &q1)) 
    {
        printf("\e[91mFailed\e[0m\n");
    }
    else
    {
        printf("\e[92mSuccess\e[0m\n");
    }
    
    printf("Creating queue /q2\n");
    if (queue_Create("/q2", &q2))
    {
        printf("\e[91mFailed\e[0m\n");
    }
    else
    {
        printf("\e[92mSuccess\e[0m\n");
    }
    
    printf("Putting 4 into queue 1\n");
    if (queue_Write(q1, 4))
    {
        printf("\e[91mFailed\e[0m\n");
    }
    else
    {
        printf("\e[92mSuccess\e[0m\n");
    }
    
    printf("Reading from queue 1\n");
    int data; 
    if (queue_Read(q1, &data)) 
    {
        printf("\e[91mFailed\e[0m\n");
    }
    else
    {
        printf("\e[92mReads %d from queue 1\e[0m\n", data);
    }

    printf("Trying to read from queue 2, which is empty\n");
    if (queue_Read(q2, NULL))
    {
        printf("\e[92mNothing to read\e[0m\n");    
    }
    else
    {
        printf("\e[91mSomething was read\e[0m\n");
    }

    printf("Puts the data from queue 1 multiplied by 3 into queue 2\n");
    if (queue_Write(q2, data * 3)) 
    {
        printf("\e[91mFailed\e[0m\n");
    }
    else
    {
        printf("\e[92mSuccess\e[0m\n");
    }
    
    printf("Reading from queue 2\n");
    int data2;
    if (queue_Read(q2, &data2))
    {
        printf("\e[91mFailed\e[0m\n");
    }
    else
    {
        printf("\e[92mReads %d from queue 2\e[0m\n", data2);
    }

    printf("Tries to print more messages to the queue than it has room for\n");
    for (int i=0; i<10; i++) {
        queue_Write(q1, 1);
    }
    if (queue_Write(q1, 1)) 
    {
        printf("\e[92mFailed\e[0m\n");
    }
    else
    {
        printf("\e[91mSuccess\e[0m\n");
    }

    printf("Done.\n");

    return 0;
}
