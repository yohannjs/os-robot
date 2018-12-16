#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <mqueue.h>
#include <stdbool.h>
#include <unistd.h>

#include "coms.h"

static const size_t max_msg = 58;

static bool online = false; 

static int socket;

static mqd_t rq;
static mqd_t tq;

int coms_Init(char* server_address, mqd_t *receive_queue, mqd_t *transmit_queue)
{
    // Init
    struct sockaddr_rc addr;
    socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROT_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel= (uint8_t) 1;
    str2ba(server_address, &addr.rc_bdaddr);
    int status = connect(socket, (struct sockaddr_rc *) &addr, sizeof(addr));
    if (status) 
    {
        printf("[  COMS  ] Failed to connect to server\n");
    } 
    else 
    {
        printf("[  COMS  ] Connected to server at %s\n", server_address);
        online = true;
        return 0;
    }
    return 1;    
}

void* coms_Handler(void *param)
{
    while (online)
    {
        char *receive_msg;
        int read_bytes = read(socket, receive_msg, max_msg);
        if (read_bytes =< 0)
        {
            printf("[  COMS  ] Server dropped connection.\n");
            if (coms_DeInit())
            {
                printf("[  COMS  ] Insane error! Shutting down!\n");
                exit(1);
            }
            break;   
        } else {
            int type = receive_msg[4];
            switch (type)
            {
                case COMS_ACK:
                    break;
                case COMS_START:
                    break;
                case COMS_STOP:
                    break;
                case COMS_KICK:
                    break;
                case COMS_SCORE:
                    break;
                case COMS_CUSTOM:
                    break;
                default:
                    printf("[  COMS  ] Received unknown message\n");
            }
            
            
            // TODO Send to receive message queue

            // TODO Error handling
        }

        int transmit_msg;
        if (0) // TODO Read from transmit queue
        {
            *((uint16_t *) msg) = 0; // Msg ID is hopefully useless
            msg[2] = COMS_GROUP; 
            msg[3] = 0xFF;
            msg[4] = 4;
            msg[5] = 1;
            write(socket, msg, 6);
        }
    }
}

int coms_DeInit(void)
{
    if (online)
    {
        printf("[  COMS  ] Disconnecting...\n");
        online = false;
        sleep(2);
        return 0;
    } else {
        printf("[  COMS  ] Can't disconnect when I'm not connected.\n");
    }
    return 1;
}

