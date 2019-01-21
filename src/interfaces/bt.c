#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "utils.h"
#include "bt.h"

static const char *mn = "   BT   ";

static int bt_server_address;
static int bt_team_id; 

static int bt_socket;
static unsigned int bt_msg_id = 0;

static int ReadMessage(char *buffer)
{
    int bytes_read = read(bt_socket, buffer, BT_MAX_MSG_LENGTH);
    if (bytes_read <= 0)
    {
        utils_Err(mn, "Unable to read from server");
        return -1;
    }
    return bytes_read;
}

int bt_Connect(const char *server_address, int team_id)
{
    bt_server_address = server_address;
    bt_team_id = team_id;

    struct sockaddr_rc addr = {0};
    bt_socket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba(server_address, &addr.rc_bdaddr);
    int status = connect(bt_socket, (struct sockaddr *) &addr, sizeof(addr));
    if (status == 0) 
    {
        utils_Log(mn, "Connected to server");
        return 0;
    }
    utils_Err(mn, "Could not connect to server");
    close(bt_socket);
    return 1;
}

int bt_WaitForStartMessage()
{
    char msg[58];
    do 
    {
        if (ReadMessage(msg) <= 0)
        {
            return 1;
        }
    }
    while(msg[4] != BT_MSG_START);
    utils_Log(mn, "Received start message.");
    return 0;
}

int bt_SendScoreMessage(int long_shot)
{
    char msg[58];
    *((uint16_t *) msg) = bt_msg_id++;
    msg[2] = bt_team_id;
    msg[3] = 0xFF;
    msg[4] = BT_MSG_SCORE;
    if (long_shot)
    {
        msg[5] = 3;
    }
    else
    {
        msg[5] = 1;
    }
    int sent_bytes = write(bt_socket, msg, 6);
    if (sent_bytes <= 0)
    {
        utils_Err(mn, "Score message could not be sent");
        return -1;
    }
    return sent_bytes; 
}

int bt_Disconnect()
{
    if (close(bt_socket) == -1)
    {
        utils_Err(mn, "Error occured when closing socket");
        return 1;
    }
    utils_Log(mn, "Disconnected from server");
    return 0;
}
