#ifndef LOGGER_H
#define LOGGER_H

int logger_log(char* file, char* string);
int logger_info(char* file, char* string);
int logger_warning(char* file, char* string);
int logger_error(char* file, char* string);

#endif
