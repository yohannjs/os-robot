#ifndef QUEUE_H
#define QUEUE_H

int queue_CreateWriteDescriptor(char *name, mqd_t *mq);

int queue_CreateReadDescriptor(char *name, mqd_t *mq);

int queue_Write(mqd_t mq, int data);

int queue_Read(mqd_t mq, int *data);

#endif
