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

int coms_Init(char* server_address)
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

int coms_Receive(void)
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
    } 
    else 
    {
        int type = receive_msg[4];
        switch (type)
        {
            case COMS_ACK:
                return -1;
            case COMS_START:
                return COMS_START;
            case COMS_STOP:
                return COMS_STOP;
            case COMS_KICK:
                if (receive_msg[5] == COMS_GROUP)
                    return COMS_KICK;
                else
                    return -1;
            case COMS_SCORE:
                return -1;
            case COMS_CUSTOM:
                return -1;
            default:
                printf("[  COMS  ] Received unknown message\n");
        }       
    }
}

int coms_WaitForMessage(void)
{
    int msg;
    do {
        msg = coms_receive();
    }
    while (msg == -1);
    return msg;
}

int coms_SendScore(bool long_shot)
{
    int transmit_msg;
    *((uint16_t *) msg) = 0; // Msg ID is hopefully useless
    msg[2] = COMS_GROUP; 
    msg[3] = 0xFF;
    msg[4] = COMS_SCORE;
    if (long_shot)
        msg[5] = 3;
    else
        msg[5] = 1;
    write(socket, msg, 6);
    
    return 0;
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

