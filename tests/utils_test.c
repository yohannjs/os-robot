#include <stdio.h>

#include "utils.h"

static const char* mn = "  UTIL  ";

int main()
{
    utils_Log(mn, "Ordinary logging works.");
    utils_Err(mn, "Errors too!");
    utils_Log(mn, "Now I'm supposed to wait for 2.5 seconds...");
    utils_Sleep(2500);
    utils_Log(mn, "You will have to judge how well it went.");
    int voltage = utils_Battery();
    utils_LogInt(mn, "Battery voltage: ", voltage);
    utils_ErrInt(mn, "Error number: ", 0);
    return 0;
}
