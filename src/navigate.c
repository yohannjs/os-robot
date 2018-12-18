#include "drive.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
  RIGHT = 90,
  LEFT = 270,
  UP = 0,
  DOWN = 180,
  LEFT_DIAGONAL = 320,
  RIGHT_DIAGONAL = 40,
} direction;

typedef enum{
  MIDDLE = 20,
  DIAGONAL = 40,
  SIDE = 30,
} searchpoint_distance;

static const int START_X = 60;
static const int START_Y = 27;
//static const int Y_SEARCH_OFFSET = 20;
static const int SEARCH_THROWLINE_OFFSET = 33;
//static const int X_SERCHPOINT_OFFSET = 30;
//static const int DIAGONAL_SEARCHPOINT_ANGLE = 40;
//static const int DIAGONAL_SEARCHPOINT_DISTANCE = 40;
static searchpoint_distance current_robot_distance;
static direction current_robot_heading;
static int ball_distance = 0;
static int ball_direction = 0;


void navigation_GoToScanPosition(searchpoint_distance distance, direction direction){
  drive_SetHeading(direction);
  sleep(2);
  drive_GoForward(distance);
  sleep(2);
  current_robot_heading = direction;
  current_robot_distance = distance;
}

void navigation_ReturnFromScanPosition(){
  drive_SetHeading(current_robot_heading);
  sleep(2);
  drive_BackDistance(current_robot_distance);
  sleep(2);
}
//should this also register objects somewhere?
void navigation_MoveToBall(int distance_to_ball, int ball_heading){
  ball_distance = distance_to_ball-13;
  ball_direction = ball_heading;
  drive_SetHeading(ball_heading);
  drive_GoDistance(ball_distance);
}

void navigation_ReturnToScanPosition(){
  drive_BackDistance(ball_distance);
  sleep(3);
  drive_Turn(-ball_direction);
  sleep(2);
}

void navigation_GoToShootingPosition(){
  bool is_on_line = false;
  drive_GoForward();
  while(is_on_line == false){
    is_on_line = false;//detect_OnLine();
  }
  drive_Stop();
}
void navigation_ReturnAfterThrow(){
  drive_BackDistance(SEARCH_THROWLINE_OFFSET);
}
/*
void navigation_GoToStart(){
  //navigation_GoToPosition(60,27);
}
*/

void navigation_RecalibrateGyro(){
  drive_GoDistance(70);
  sleep(1);
  drive_ResetGyro();
  drive_BackDistance(61);
}
