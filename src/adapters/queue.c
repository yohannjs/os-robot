#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>

#include "queue.h"

static const size_t queue_size = 10;
static const size_t msg_size = sizeof(int);

static int queue_CreateDescriptor(char *name, mqd_t *mq, int flags)
{
    if (name[0] != '/')
    {
        printf("[ QUEUE  ] Queue name must start with /\n");
        return 1;
    }
    struct mq_attr attr;
    attr.mq_maxmsg = queue_size;
    attr.mq_msgsize = msg_size;
    attr.mq_flags = 0;
    *mq = mq_open(name, flags, 0666, &attr);
    if (*mq == (mqd_t)-1)
    {
        printf("[ QUEUE  ] Queue %s could not be created\n", name);
        return 1;
    }
    return 0;
}

int queue_CreateWriteDescriptor(char *name, mqd_t *mq)
{
    return queue_CreateDescriptor(name, mq, O_CREAT | O_WRONLY | O_NONBLOCK);
}

int queue_CreateReadDescriptor(char *name, mqd_t *mq)
{
    return queue_CreateDescriptor(name, mq, O_RDONLY | O_NONBLOCK);
}

int queue_Write(mqd_t mq, int data)
{
    mq_send(mq, (char*) &data, msg_size, NULL);
    return 0;
}

int queue_Read(mqd_t mq, int *data)
{
    mq_receive(mq, (char*) data, msg_size, 1);
    return 0;
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
