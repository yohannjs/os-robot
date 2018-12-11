#include "../interfaces/logger.h"

int main()
{
    logger_init("log.txt");

    logger_log("Woohoo");
    logger_info("Jeg");
    logger_warning("er");
    logger_error("en gnom");
    return 0;
}
