#ifndef UTILS_H
#define UTILS_H

/**
 * Makes the current thread wait for a specified number of milliseconds.
 */
void utils_Sleep(int ms);

/**
 * Prints a message on a standardized format with the name of the calling
 * module.
 */
void utils_Log(const char *module_name, const char *msg);

/**
 * Same as utils_Log but print is bright red.
 */
void utils_Err(const char *module_name, const char *msg);

/**
 * Prints a message with following number (integer) on standardized form with
 * module name.
 */
void utils_LogInt(const char *module_name, const char *msg, int number);

/**
 * Same as utils_LogInt but in error red
 */
void utils_ErrInt(const char *module_name, const char *msg, int number);

/**
 * Returns the current battery voltage of the EV3 lego brick as an int. Unit
 * is volts.
 */
int utils_Battery(void);

#endif
