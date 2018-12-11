#ifndef CAKE_H
#define CAKE_H

int cake_Init(void);
void* cake_Server(void* param);
void cake_Send(int pieces);
void cake_Stop(void);

#endif
