#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>

#include "cake.h"

static mqd_t mq_rd; // MQ receive descriptor
static mqd_t mq_td; // MQ transmit descriptor

int queue_Create(char *name, mqd_t *mq, int max_length)
{
    if (name[0] != '/')
    {
        printf("\e[91m[QUEUE] Queue name must start with /\e[0m\n");
        return 1;
    }
    struct mq_attr attr;
    attr.mq_maxmsg = max_length;
    attr.mq_msgsize = sizeof(int);
    attr.mq_flags = 0;
    *mq = mq_open(name, O_CREAT | O_RDWR |O_NONBLOCK, 0666, &attr);
    if (*mq == (mqd_t)-1)
    {
        printf("\e91m[QUEUE] Queue %s could not be created\e[0m\n", name);
        return 1;
    }
    return 0;
}

void queue_Write(mqd_t mq, int data)
{
    mq_send(mq, (char*) &data, sizeof(int), NULL);
}

int queue_Read(mqd_t mq)
{
    int data = 0;
    mq_receive(mq, (char*) &data, sizeof(int), 1);
    return data;
}
/*
int cake_Init(void)
{
    mq_rd = mq_open("/cake", O_RDONLY, 0666, &attr);

    return 0;
}

void* cake_Server(void* param)
{
    int pieces = (int) param;
    
    printf("I am the cake master!\n");
    while (1)
    {
        printf("I can never be destroyed!\n");
        int data = 0;
        mq_receive(mq_rd, (char*) &data, sizeof(int), NULL);
        if (data == 0)  
        {
            printf("AAGH! Getting 0 cakes is my only weakness!!\n");
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
    cake_Send(0);
}

void cake_Send(int pieces)
{
    mq_send(mq_td, (char*) &pieces, sizeof(int), 1);
}
*/
