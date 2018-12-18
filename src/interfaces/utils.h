#ifndef UTILS_H
#define UTILS_H

/**
 * Makes the current thread wait for a specified number of milliseconds.
 */
void utils_sleep(int ms);

/**
 * Prints a message on a standardized format with the name of the calling
 * module.
 */
void utils_log(const char *module_name, const char *msg);

/**
 * Same as utils_log but print is bright red.
 */
void utils_err(const char *module_name, const char *msg);

/**
 * Returns the current battery voltage of the EV3 lego brick as a float. Unit
 * is volts.
 */
float utils_battery(void);

#endif
