#ifndef NAVIGATE_H
#define NAVIGATE_H

typedef enum dir{
  RIGHT = 90,
  LEFT = 270,
  UP = 0,
  DOWN = 180,
  LEFT_DIAGONAL = 326,
  RIGHT_DIAGONAL = 34,
} direction;

typedef enum dist{
  MID_SIDE = 20,
  EAST_WEST = 40,
  NORTH_SOUTH = 30,
  DIAGONAL = 36,
} searchpoint_distance;

typedef enum {
  SOUTH_EAST = 1,
  NORTH_EAST = 2,
  NORTH_WEST = 3,
  SOUTH_WEST = 4,
  MIDDLE = 5;
} p;

void navigation_RecalibrateGyro();
//void navigation_GoToStart();

void navigation_GoToScanPosition(p search_point);
void navigation_MoveToBall(int distance_to_ball, int ball_heading);
void navigation_ReturnToScanPosition();
void navigation_ReturnFromScanPosition();
void navigation_GoToShootingPosition();
void navigation_ReturnAfterThrow();
void navitation_GoToDropPosition();
//void navigation_GoToSideOfObject(direction heading, direction side );

#endif
