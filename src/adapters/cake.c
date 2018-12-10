#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>

#include "cake.h"

static mqd_t mq_rd; // MQ receive descriptor
static mqd_t mq_td; // MQ transmit descriptor

int cake_Init(void)
{
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(int);
    attr.mq_flags = 0;
    
    mq_td = mq_open("/cake", O_CREAT | O_WRONLY, 0666, &attr);
    mq_rd = mq_open("/cake", O_RDONLY, 0666, &attr);

    return 0;
}

void* cake_Server(void* param)
{
    int pieces = (int) param;
    
    printf("I am the cake master!\n");
    while (1)
    {
        sleep(1);
        printf("I can never be destroyed!\n");
        int data = 0;
        mq_receive(mq_rd, (char*) &data, sizeof(int), NULL);
        if (data == 0)  
        {
            printf("AAGH! Not eating cake is my only weakness!!\n");
            break;
        }
        else
            printf("By giving me %d cakes you've made me more powerful!\n", data);
    }
    pthread_exit(NULL);
    return NULL;
}

void cake_Stop(void)
{
    int data = 0;
    mq_send(mq_td, (char*) &data, sizeof(int), 1); 
}

