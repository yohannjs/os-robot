#ifndef COMS_H
#define COMS_H

#define COMS_GROUP 5

#define COMS_ACK 0
#define COMS_START 1
#define COMS_STOP 2
#define COMS_KICK 3
#define COMS_SCORE 4
#define COMS_CUSTOM 8

/**
 * Initialization function.
 * Establishes connection with server.
 *
 * @param *server_address 
 *      A string containing the bt address of the server
 * @param *receive_queue 
 *      A pointer to the queue that is to be used to read received messages
 *      The queue will be made by the module. 
 *      The queue can be populated with the following messages:
 *      1 : Server sent a START message
 *      2 : Server sent a STOP message
 *      3 : Server sent a KICK message and it us that has been kicked (will
 *          not be placed in queue if someone else is kicked)
 *      ACKs will be handled by the coms module
 *      CUSTOM messages will be printed by the coms module but not added to
 *      the queue
 *      SCORE messages shall not be sent to Kob-E, it is the one who sends
 * @param *transmit_queue
 *      A pointer to the queue that shall hold the messages to be received.
 *      Kob-E shall only send SCORE messages, so no matter what you put in the
 *      queue it will result in a SCORE message.
 *  
 * @returns status
 *      0 = success
 *      1 = failure
 */
int coms_Init(char *server_address, mqd_t *receive_queue, mqd_t *transmit_queue);

/**
 * Coms module message handling loop.
 * Is to be run as a pthread.
 * Communicate with it through the queues given to coms_Init.
 * Parameter is unused, but required by pthread, just pass it NULL.
 */
//void *coms_Handle(void *param);

/**
 * Deinitialization function.
 * Disconnects from server.
 *
 * @returns status
 *      0 = success
 *      1 = couldn't disconnect
 */
int coms_DeInit(void);

int coms_Read(void);

int coms_SendScore(bool long_shot);

int coms_WaitForMessage(void);

#endif
