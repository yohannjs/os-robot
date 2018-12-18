#include "utils.h"

static const char* mn = "  UTIL  ";

int main()
{
    utils_log(mn, "Ordinary logging works.");
    utils_err(mn, "Errors too!");
    utils_log(mn, "Now I'm supposed to wait for 2.5 seconds...");
    utils_sleep(2500);
    utils_log(mn, "You will have to judge how well it went.");

    return 0;
}
