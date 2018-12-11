#ifndef QUEUE_H
#define QUEUE_H

int queue_Create(char *name, mqd_t *mq, int max_length);
void queue_Write(mqd_t mq, int data);
int queue_Read(mqd_t mq);
#endif
