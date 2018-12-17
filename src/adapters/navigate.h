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
  //MIDDLE = 20,
  DIAGONAL = 40,
  SIDE = 20,
} searchpoint_distance;

typedef struct {
  searchpoint_distance dist;
  direction dir;
} point;


const point SOUTH_EAST {SIDE, RIGHT};
const point SOUTH_WEST {SIDE, LEFT};
const point NORTH_EAST {DIAGONAL, RIGHT_DIAGONAL};
const point NORTH_WEST {DIAGONAL, LEFT_DIAGONAL};


void navigation_RecalibrateGyro();
//void navigation_GoToStart();

void navigation_GoToScanPosition(point search_point);
void navigation_MoveToBall(int distance_to_ball, int ball_heading);
void navigation_ReturnToScanPosition();
void navigation_ReturnFromScanPosition();
void navigation_GoToShootingPosition();
void navigation_ReturnAfterThrow();
void navitation_GoToDropPosition();
//void navigation_GoToSideOfObject(direction heading, direction side );

#endif
