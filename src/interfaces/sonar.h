#ifndef SONAR_H
#define SONAR_H

/**
 * Initializes EV3 ultrasound sensor
 *
 * @returns status code
 *      0 = success
 *      1 = ev3 not initialized
 *      2 = could not find sonar sensor
 */
int sonar_init(void);

/**
 * Gets the current distance read by the sonar
 *
 * @returns distance in millimeters
 */
int sonar_getDistance(void);

#endif
