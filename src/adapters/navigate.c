
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "detect.h"
#include "drive.h"
#include "navigate.h"

static const int START_X = 60;
static const int START_Y = 27;//changed must measure and change

static const int START_THROWLINE_OFFSET = 24;//changed 17/12 from 28 to 24
static int ball_distance = 0;
static int ball_direction = 0;
static p current_point = MIDDLE;

void navigation_Init(){
  drive_Init();
}

void navigation_GoToScanPosition(p search_point){
  if(current_point == MIDDLE){
    switch (search_point) {
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
    }
  }else if(current_point == SOUTH_EAST){
      switch (search_point) {
        case MIDDLE:
          printf("not supposed to go here from south_EAST\n");
          break;
        case NORTH_EAST:
          drive_SetHeading(UP);
          drive_GoDistance(NORTH_SOUTH);
          break;
        case NORTH_WEST:
          printf("not supposed to go here from south_EAST\n");
          break;
        case SOUTH_WEST:
          drive_SetHeading(LEFT);
          drive_GoDistance(EAST_WEST);
          break;
      }
    }else if(current_point == NORTH_EAST){
        switch (search_point) {
          case MIDDLE:
            printf("not supposed to go here from NORTH_EAST\n");
            break;
          case SOUTH_EAST:
            drive_SetHeading(DOWN);
            drive_GoDistance(NORTH_SOUTH);
            break;
          case NORTH_WEST:
            drive_SetHeading(LEFT);
            drive_GoDistance(EAST_WEST);
            break;
          case SOUTH_WEST:
            printf("not supposed to go here from NORTH_EAST\n");
            break;
        }
      }else if(current_point == NORTH_WEST){
          switch (search_point) {
            case MIDDLE:
              printf("not supposed to go here from NORTH_WEST\n");
              break;
            case SOUTH_EAST:
              printf("not supposed to go here from NORTH_WEST\n");
              drive_SetHeading(DOWN);
              drive_GoDistance(NORTH_SOUTH);
              break;
            case NORTH_EAST:
              drive_SetHeading(RIGHT);
              drive_GoDistance(EAST_WEST);
              break;
            case SOUTH_WEST:
              drive_SetHeading(DOWN);
              drive_GoDistance(NORTH_SOUTH);
              break;
          }
        }else if(current_point == SOUTH_WEST){
            switch (search_point) {
              case MIDDLE:
                printf("not supposed to go here from SOUTH_WEST\n");
                break;
              case SOUTH_EAST:
                drive_SetHeading(RIGHT);
                drive_GoDistance(EAST_WEST);
                break;
              case NORTH_EAST:
                printf("not supposed to go here from SOUTH_WEST\n");
                break;
              case NORTH_WEST:
                drive_SetHeading(UP);
                drive_GoDistance(NORTH_SOUTH);
                break;
            }
          }
  current_point = search_point;
}

void navigation_ReturnFromScanPosition(){
  switch (current_point) {
    case SOUTH_EAST:
      drive_SetHeading(RIGHT);
      drive_BackDistance(MID_SIDE);
    case NORTH_EAST:
      drive_SetHeading(RIGHT_DIAGONAL);
      drive_BackDistance(DIAGONAL);
    case NORTH_WEST:
      drive_SetHeading(LEFT_DIAGONAL);
      drive_BackDistance(DIAGONAL);
    case SOUTH_WEST:
    drive_SetHeading(LEFT);
    drive_BackDistance(MID_SIDE);
  }
  current_point = MIDDLE;
}
//should this also register objects somewhere?
void navigation_MoveToBall(int distance_to_ball, int ball_heading){
  ball_distance = distance_to_ball-13;
  ball_direction = ball_heading;
  printf("MoveToBall: setting heading %d\n", ball_direction);
  drive_SetHeading(ball_heading);
  printf("MoveToBall: going distance %d\n", ball_distance);
  drive_GoDistance(ball_distance);
}

void navigation_ReturnToScanPosition(){
  drive_BackDistance(ball_distance);
  printf("ReturnToScanPosition: backing %d\n", ball_distance);
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

void navitation_GoToDropPosition(){
  int distance_to_drop_position = 55;
  drive_GoDistance(distance_to_drop_position);
}

void navigation_ReturnAfterDrop(){
  int distance_from_drop_position = 55;
  drive_BackDistance(distance_from_drop_position);
}

void navigation_RecalibrateGyro(){
  drive_GoDistance(70);
  drive_ResetGyro();
  drive_BackDistance(61);
}
