// Drive module header file. The functions intended for external use are:
// drive_TurnRight, drive_TurnLeft, drive_GoDistance, drive_BackDistance
// and drive_GetHeading.



//initialize functions
void drive_Init();
int drive_InitTachos();
void drive_SensorInit();

//drive functions for external use
void drive_TurnRight(int deg);
void drive_TurnLeft(int deg);
void drive_GoDistance(int distance);
void drive_BackDistance(int distance);
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
void drive_SetHeading(int heading);
