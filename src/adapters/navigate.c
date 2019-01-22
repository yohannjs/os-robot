
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "detect.h"
#include "drive.h"
#include "navigate.h"
#include "utils.h"

// static const int START_X = 60;
// static const int START_Y = 27;//changed must measure and change

static const int START_THROWLINE_OFFSET = 24;
static int ball_distance = 0;
static int ball_direction = 0;
static p current_point = MIDDLE;

void navigation_Init(){
  drive_Init();
}

void navigation_GoToScanPosition(p search_point)
{
  if(current_point == MIDDLE)
  {
    switch (search_point)
    {
      case SOUTH_EAST:
        drive_SetHeading(RIGHT);
        drive_GoDistance(MID_SIDE);
        break;
      case NORTH_EAST:
        drive_SetHeading(RIGHT_DIAGONAL);
        drive_GoDistance(DIAGONAL);
        break;
      case NORTH_WEST:
        drive_SetHeading(LEFT_DIAGONAL);
        drive_GoDistance(DIAGONAL);
        break;
      case SOUTH_WEST:
        drive_SetHeading(LEFT);
        drive_GoDistance(MID_SIDE);
        break;
      default:
        printf("[NAVIGATE] Already here.\n");
    }
  }
  else if(current_point == SOUTH_EAST)
  {
    switch (search_point)
    {
      case NORTH_EAST:
        drive_SetHeading(UP);
        drive_GoDistance(NORTH_SOUTH);
        break;
      case SOUTH_WEST:
        drive_SetHeading(LEFT);
        drive_GoDistance(EAST_WEST);
        break;
      case MIDDLE:
        drive_SetHeading(LEFT);
        drive_GoDistance(MID_SIDE);
      default:
        printf("[NAVIGATE] Not supposed to go here.\n");

    }
  }
  else if(current_point == NORTH_EAST)
  {
    switch (search_point)
    {
      case SOUTH_EAST:
        drive_SetHeading(DOWN);
        drive_GoDistance(NORTH_SOUTH);
        break;
      case NORTH_WEST:
        drive_SetHeading(LEFT);
        drive_GoDistance(EAST_WEST);
        break;
      default:
        printf("[NAVIGATE] Not supposed to go here.\n");
        break;
    }
  }
  else if(current_point == NORTH_WEST)
  {
    switch (search_point)
    {
      case NORTH_EAST:
        drive_SetHeading(RIGHT);
        drive_GoDistance(EAST_WEST);
        break;
      case SOUTH_WEST:
        drive_SetHeading(DOWN);
        drive_GoDistance(NORTH_SOUTH);
        break;
      default:
        printf("[NAVIGATE] Not supposed to go here.\n");
    }
  }
  else if(current_point == SOUTH_WEST)
  {
    switch (search_point)
    {
      case SOUTH_EAST:
        drive_SetHeading(RIGHT);
        drive_GoDistance(EAST_WEST);
        break;
      case NORTH_WEST:
        drive_SetHeading(UP);
        drive_GoDistance(NORTH_SOUTH);
        break;
      case MIDDLE:
        drive_SetHeading(RIGHT);
        drive_GoDistance(MID_SIDE);
      default:
        printf("[NAVIGATE] Not supposed to go here.\n");
    }
  }
  // printf("current point used = %d \n", current_point);
  // printf("search point used = %d \n", search_point);
  current_point = search_point;
}

void navigation_ReturnFromScanPosition(){
  switch (current_point)
  {
    case SOUTH_EAST:
      drive_SetHeading(RIGHT);
      drive_BackDistance(MID_SIDE);
      break;
    case NORTH_EAST:
      drive_SetHeading(RIGHT_DIAGONAL);
      drive_BackDistance(DIAGONAL);
      break;
    case NORTH_WEST:
      drive_SetHeading(LEFT_DIAGONAL);
      drive_BackDistance(DIAGONAL);
      break;
    case SOUTH_WEST:
      drive_SetHeading(LEFT);
      drive_BackDistance(MID_SIDE);
      break;
    default:
      printf("[ReturnFromScanPosition] Already in starting point.\n");
  }
  current_point = MIDDLE;
  drive_SetHeading(UP);
}
//should this also register objects somewhere?
void navigation_MoveToBall(int distance_to_ball, int ball_heading){
  ball_distance = distance_to_ball-13;
  ball_direction = ball_heading;
  printf("[NAVIGATE] MoveToBall: setting heading %d\n", ball_direction);
  drive_SetHeading(ball_heading);
  printf("[NAVIGATE] MoveToBall: going distance %d\n", ball_distance);
  drive_GoDistance(ball_distance);
}

void navigation_AdjustBallDistance(int distance_to_ball){
  int to_move = distance_to_ball - 13;
  utils_Sleep(300);
  drive_GoDistance(to_move);
  ball_distance = ball_distance + to_move;
}

void navigation_ReturnToScanPosition(){
  drive_BackDistance(ball_distance);
  printf("[NAVIGATE] ReturnToScanPosition: backing %d\n", ball_distance);
}

void navigation_GoToThrowPosition(){
  drive_GoDistance(15);
  bool is_on_line = false;
  drive_GoForward();
  while(is_on_line == false){
    is_on_line = detect_OnLine();
  }
  drive_Stop();
}

void navigation_ReturnAfterThrow(){
  drive_BackDistance(START_THROWLINE_OFFSET);
}

void navigation_GoToDropPosition(){
  int distance_to_drop_position = 59;
  drive_GoDistance(distance_to_drop_position);
  utils_Sleep(200);
  drive_ResetGyro();
  utils_Sleep(200);
  drive_BackDistance(2);
}

void navigation_ReturnAfterDrop(){
  int distance_from_drop_position = 53;
  drive_BackDistance(distance_from_drop_position);
}

void navigation_RecalibrateFront(){
  drive_GoDistance(70);
  utils_Sleep(200);
  drive_ResetGyro();
  utils_Sleep(500);
  //recalibrate before shooting? in that case: go less forward and
  //stop backing when you see a black line?
  drive_BackDistance(55);
}

void navigation_RecalibrateSide(dir side){
  drive_SetHeading(side);
  drive_GoDistance(50);
  utils_Sleep(300);
  //drive_ResetGyro();
  //utils_Sleep(500);
  drive_BackDistance(29);
}


void navigation_RecalibrateBeforeScore(){
  drive_GoDistance(70);
  utils_Sleep(200);
  drive_ResetGyro();
  utils_Sleep(500);
  drive_BackDistance(20);
  bool is_on_line = false;
  drive_GoBackward();
  while(is_on_line == false){
    is_on_line = detect_OnLine();
  }
  drive_Stop();
  utils_Sleep(300);
}
