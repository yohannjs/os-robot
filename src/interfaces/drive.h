#ifndef DRIVE_H
#define DRIVE_H
// Drive module header file. The functions intended for external use are:
// drive_TurnRight, drive_TurnLeft, drive_GoDistance, drive_BackDistance
// and drive_GetHeading.



//initialize functions
void drive_Init();
int drive_InitTachos();
void drive_SensorInit();

//drive functions for external use
void drive_TurnDegrees(int deg, int speed); //speed 0 to 100, 100 == max_speed
void drive_TurnRight(int deg);
void drive_TurnLeft(int deg);
void drive_GoDistance(int distance);
void drive_BackDistance(int distance);
int drive_MotorStatus(); //returns 0 if motor is not driving, 1 otherwise.
void drive_SetHeading(int desired_heading);
//drive functions for internal use
void drive_Turn(int deg);

void drive_TurnRightForever(int speed);
void drive_TurnLeftForever(int speed);
void drive_GoForward();
void drive_GoBackward();
void drive_Stop();
//sensor functions
int drive_GetGyroValue();
int drive_GetHeading();
void drive_ResetGyro();

#endif
