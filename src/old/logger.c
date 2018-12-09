#include "logger.h"
#include <stdio.h>

int logger_log(char* file, char* string)
{
    printf("%s\n", string);
    
    FILE* f;
    f = fopen(file, "a");
    fprintf(f, "[LOG] %s\n", string);
    fclose(f);
}

int logger_info(char* file, char* string)
{
    printf("\e[96m%s\e[0m\n", string);

    FILE* f;
    f = fopen(file, "a");
    fprintf(f, "[INF] %s\n", string);
    fclose(f);
}

int logger_warning(char* file, char* string)
{
    printf("\e[93m%s\e[0m\n", string);

    FILE* f;
    f = fopen(file, "a");
    fprintf(f, "[WRN] %s\n", string);
    fclose(f);
}

int logger_error(char* file, char* string)
{
    printf("\e[91m%s\e[0m\n", string);

    FILE* f;
    f = fopen(file, "a");
    fprintf(f, "[ERR] %s\n", string);
    fclose(f);
}
