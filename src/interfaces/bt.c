#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "bt.h"
#include "utils.h"

#define BT_SERV_ADDR    "38:ba:f8:5a:6b:9d"     
#define BT_TEAM_ID      1                      

static const char *mn = "   BT   ";

static int s;
static uint16_t msgId = 0;

static int ReadMessage (char *buffer) {
  int bytes_read = read (s, buffer, BT_MAX_MSG_LENGTH);

  if (bytes_read <= 0) {
    utils_Err(mn, "Server unexpectedly closed connection");
    return -1;
  }

  return bytes_read;
}

int bt_Connect() {
    struct sockaddr_rc addr = { 0 };
    int status;

    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba (BT_SERV_ADDR, &addr.rc_bdaddr);

    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    if (status != 0)
    {
        utils_Err(mn, "Error!");
        return 1;
    }

    return 0;
}

int bt_SendScoreMessage(int long_shot) {
    char string[BT_MAX_MSG_LENGTH];
    
    *((uint16_t *) string) = msgId++;
    string[2] = BT_TEAM_ID;
    string[3] = 0xFF;
    string[4] = BT_MSG_SCORE;
    string[5] = long_shot ? 3 : 1; 
    int bytenum = write(s, string, 6);
    if (bytenum <= 0) {
        utils_Err(mn, "Could not send score message");
        return -1;
    }
    return bytenum;
}

void bt_WaitForStartMessage() {
    char string[BT_MAX_MSG_LENGTH];
    do {
        ReadMessage(string);
    } while (string[4] != BT_MSG_START);
}

void bt_WaitForStopMessage() {
    char string[BT_MAX_MSG_LENGTH];
    do {
        ReadMessage(string);
    } while (string[4] != BT_MSG_STOP);
}

void bt_Disconnect() {
    close(s);
}

