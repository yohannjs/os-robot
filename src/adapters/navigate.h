#ifndef NAVIGATE_H
#define NAVIGATE_H

typedef enum dir{
  RIGHT = 90,
  LEFT = 270,
  UP = 0,
  DOWN = 180,
  LEFT_DIAGONAL = 320,
  RIGHT_DIAGONAL = 40,
} direction;

typedef enum dist{
  MIDDLE = 20,
  DIAGONAL = 40,
  SIDE = 30,
} searchpoint_distance;

void navigation_RecalibrateGyro();
//void navigation_GoToStart();
void navigation_Init();

void navigation_GoToScanPosition(searchpoint_distance distance, direction direction);
void navigation_MoveToBall(int distance_to_ball, int ball_heading);
void navigation_ReturnToScanPosition();
void navigation_ReturnFromScanPosition();
void navigation_GoToThrowPosition();
void navigation_ReturnAfterThrow();
void navigation_ReturnAfterDrop();
void navitation_GoToDropPosition();
void navigation_AdjustBallDistance(int distance_to_ball);
//void navigation_GoToSideOfObject(direction heading, direction side );

#endif
