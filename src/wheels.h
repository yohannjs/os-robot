#define Sleep( msec ) usleep(( msec ) * 1000 );

int initTachos();
void turnDegRight(int deg);
void turnRight();
void turnLeft();
void gyroTurn(int deg);
