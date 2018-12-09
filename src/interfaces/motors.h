#ifndef MOTORS_H
#define MOTORS_H

/**
 * Initializes motors
 *
 * @param number The number of motors connected to the system
 * @param ports An array containing the ports of the motors
 */
uint8_t motors_init(uint8_t number, uint8_t* ports);

/**
 * Sets the speed of motor with selected index
 *
 * @param motorIndex The index of the motor
 * @param speed The speed of the motor, 127 is max forward, -128 is max backward.
 */
void motors_setSpeed(uint8_t motorIndex, int8_t speed);

#endif
