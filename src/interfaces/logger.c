#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char* logFile;

int logger_init(char* fileName)
{
    int fileNameLength = strlen(fileName);
    logFile = malloc(sizeof(char) * fileNameLength);
    logFile = fileName;
    
    time_t rawTime;
    struct tm* timeInfo;
    time(&rawTime);
    timeInfo = localtime(&rawTime);

    FILE* f;
    f = fopen(logFile, "a");
    fprintf(f, "\nLOG START %s", asctime(timeInfo));
    fclose(f);

    return 0;
}

void logger_log(char* string)
{
    printf("%s\n", string);
    
    FILE* f;
    f = fopen(logFile, "a");
    fprintf(f, "[LOG] %s\n", string);
    fclose(f);
}

void logger_info(char* string)
{
    printf("\e[96m%s\e[0m\n", string);

    FILE* f;
    f = fopen(logFile, "a");
    fprintf(f, "[INF] %s\n", string);
    fclose(f);
}

void logger_warning(char* string)
{
    printf("\e[93m%s\e[0m\n", string);

    FILE* f;
    f = fopen(logFile, "a");
    fprintf(f, "[WRN] %s\n", string);
    fclose(f);
}

void logger_error(char* string)
{
    printf("\e[91m%s\e[0m\n", string);

    FILE* f;
    f = fopen(logFile, "a");
    fprintf(f, "[ERR] %s\n", string);
    fclose(f);
}
