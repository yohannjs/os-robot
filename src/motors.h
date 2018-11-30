

//#define motors_connect connect
/**
 * Connects to selected number of motors on selected ports
 * 
 * @param motorNum Number of motors to connect to
 * @param motorPorts Array containing the ports of the motors
 */
extern int motors_connect(int motorNum, int* motorPorts);


//#define motors_setSpeed setSpeed
/**
 * Sets the speed of a specified motor.
 *
 * @param motorIndex The index of the motor.
 * @param speed The desired speed for the motor, 0-255.
 */
extern void motors_setSpeed(int motorIndex, int speed);


//#define motors_setAngle setAngle
/**
 * Sets the desired angle of the motor, this will make the motor move.
 *
 * @param motorIndex The index of the motor to move.
 * @param angle The desired angle for the motor to move to.
 */
extern void motors_setAngle(int motorIndex, int angle);


