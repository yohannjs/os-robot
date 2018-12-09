// Drive module header file. The functions intended for external use are:
// drive_TurnRight, drive_TurnLeft, drive_GoDistance, drive_BackDistance
// and drive_GetHeading.



//initialize functions
int drive_InitTachos();
void drive_SensorInit();

//drive functions
void drive_Turn(int deg);
void drive_TurnRight(int deg);
void drive_TurnLeft(int deg);
void drive_TurnRightUntilStopped();
void drive_TurnLeftUntilStopped();
void drive_GoForward();
void drive_GoBackward();
void drive_Stop();
void drive_GoDistance(int distance);
void drive_BackDistance(int distance);
void drive_SetHeading();
//sensor functions
int drive_GetGyroValue();
int drive_GetHeading();
drive_SetHeading();
