#include <stdio.h>
#include <mqueue.h>

#include "queue.h"

int main(void)
{
    mqd_t q1r;
    mqd_t q1w;
    
    queue_CreateReadDescriptor("/q1", &q1r);
    queue_CreateWriteDescriptor("/q1", &q1w);
    
    queue_Write(q1w, 4);

    int data; 
    queue_Read(q1r, &data);

    printf("I received %d\n", data);

    return 0;
}
