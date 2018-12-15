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
        printf("[  QUEUE ] Queue name must start with /\n");
        return 1;
    }
    struct mq_attr attr;
    attr.mq_maxmsg = queue_size;
    attr.mq_msgsize = msg_size;
    attr.mq_flags = 0;
    *mq = mq_open(name, flags, 0666, &attr);
    if (*mq == (mqd_t)-1)
    {
        printf("[  QUEUE ] Queue %s could not be created\n", name);
        return 1;
    }
    return 0;
}

int queue_Create(char *name, mqd_t *mq)
{
    return queue_CreateDescriptor(name, mq, O_CREAT | O_RDWR | O_NONBLOCK);
}

int queue_Write(mqd_t mq, int data)
{
    if (mq_send(mq, (char*) &data, msg_size, NULL) == -1) {
        printf("[  QUEUE ] Message queue is full\n");
        return 1;
    }
    return 0;
}

int queue_Read(mqd_t mq, int *data)
{
    int bytes = mq_receive(mq, (char*) data, msg_size, 1);
    if (bytes == -1) 
    {
        data = 0;
        return 1;
    }
    return 0;
}
