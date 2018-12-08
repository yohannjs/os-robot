
//initialize functions
int initTachos();
void sensorInit();

//drive functions
void gyroTurn(int deg);
void turnRight();
void turnLeft();
void forward();
void backward();
void stop();

//sensor functions
int get_gyro_value();

//maybe delete these after some time
void turnLeftInterval();
void turnRightInterval();
