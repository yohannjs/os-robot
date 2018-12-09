#ifndef LOGGER_H
#define LOGGER_H

int logger_init(char* fileName);

void logger_log(char* string);
void logger_info(char* string);
void logger_warning(char* string);
void logger_error(char* string);

#endif
