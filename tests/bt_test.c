#include <stdio.h>

#include "bt.h"
#include "utils.h"

const char* mn = "  TEST  ";

const char* server_address = "38:BA:F8:F5:6B:9D";
const int team_id = 5;

int main()
{
    utils_Log(mn, "Server address:");
    utils_Log(mn, server_address);
    utils_LogInt(mn, "Team ID:", team_id);

    if (bt_Connect())
    {
        utils_Err(mn, "Error, quitting...");
        return 1;
    }
    utils_Log(mn, "Connected to server");

    utils_Log(mn, "Waiting for start message...");
    if (bt_WaitForStartMessage())
    {
        utils_Err(mn, "Error, quitting...");
        return 1;
    }

    utils_Log(mn, "Sending short throw message to server");
    if (bt_SendScoreMessage(0) <= 0)
    {
        utils_Err(mn, "Something went wrong, quitting...");
        return 1;
    }
    utils_Log(mn, "Success");
    utils_Sleep(500);
    
    utils_Log(mn, "Sending long throw message to server");
    if (bt_SendScoreMessage(1) <= 0)
    {
        utils_Err(mn, "Something went wrong, quitting...");
        return 1;
    }
    utils_Log(mn, "Success");
    utils_Sleep(500);

    utils_Log(mn, "Disconnecting from server");
    if (bt_Disconnect())
    {
        utils_Err(mn, "Something went wrong, quitting...");
        return 1;
    }
    utils_Log(mn, "Success, quitting...");
    return 0;
}

