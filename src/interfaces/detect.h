#ifndef DETECT_H
#define DETECT_H

/**
 * Initializes the detection module.
 *
 * @returns status code
 *      0 = success
 *      1 = failure
 */
int detect_Init(void);

/**
 * Gets the current distance in front of the robot detected by the sonar.
 *
 * @returns The distance in millimeters
 */
int detect_GetDistance(void);

/**
 * Gets wether the robot is over a black line.
 *
 * @returns A boolean indicating wether a black line is detected or not.
 */
bool detect_OnLine(void);

#endif
