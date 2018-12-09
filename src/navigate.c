#include "drive.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Position x goes from 0 to 119, y goes from 0 to 99

//check if allowed to drive that far before going. Is object detected closer
//than intended distance?
//calibrate when passing certain black lines in x and y?

enum direction{
  RIGHT = 90,
  LEFT = 270,
  UP = 0,
  DOWN = 180,
};
struct Position {
   int x;
   int y;
   int heading;
} pos;

void navigation_GoToPosition(int x, int y);
void navigation_InitNavigation();
int navigation_MoveForward(int distance);
void navigation_UpdatePosition(int x, int y);
main(){
//every time robot is done moving, update pos.off_x and pos.off_y with navigation_UpdatePosition.
navigation_GoToPosition(90,70);
}
//should this also register objects somewhere?
int navigation_MoveForward(int distance){
  int distance_to_obj;
  distance_to_obj = sensors_DistanceToObject();
  if (distance_to_obj > distance+5){
    drive_GoForward(distance);
    sleep(3);
    return distance;
  }else{
    drive_GoForward(distance_to_obj-5);
    sleep(3);
    return distance_to_obj -5;
  }
}

void navigation_GoToPosition(int x, int y){
  int new_position;
  int offset;
  if (pos.x > x){
    offset = pos.x-x;
    drive_SetHeading(LEFT);
    sleep(2); //need time to set heading?
    new_position = navigation_MoveForward(offset);
    navigation_UpdatePosition(-new_position,0);
  }
  if (pos.x < x){
      offset = x - pos.x;
      drive_SetHeading(RIGHT);
      sleep(2); //need time to set heading?
      new_position = navigation_MoveForward(offset)
      navigation_UpdatePosition(new_position,0);
    }
    if (pos.y > y){
      offset = pos.y-y;
      drive_SetHeading(DOWN);
      sleep(2); //need time to set heading?
      new_position = navigation_MoveForward(offset);
      navigation_UpdatePosition(0,-new_position);
    }
    if (pos.y < y){
        offset = y - pos.y;
        drive_SetHeading(UP);
        sleep(2); //need time to set heading?
        new_position = navigation_MoveForward(offset);
        navigation_UpdatePosition(0,new_position);
      }
    if (pos.x != x || pos.y != y){
      //recursive function until complete movement.
      //will get stuck here if object on destination tho..
      //also stuck if object in both x and y path.
      navigation_GoToPosition();
    }
}
void navigation_GoRightOfObj(direction heading, direction obj_side ){
  int distance_to_obj;
  if(obj_side == LEFT){drive_TurnLeft(90);}
  else if (obj_side == RIGHT){drive_TurnRight(90);}
  sleep(1);
  distance_to_obj = sensors_DistanceToObject();
  if (distance_to_obj > 15){
    drive_GoForward(10);
    sleep(2);
    if(heading == UP){
      navigation_UpdatePosition(15,0);
    }else if(heading == DOWN){
      navigation_UpdatePosition(-15,0);
    }else if(heading == LEFT){
      navigation_UpdatePosition(0,15);
    }else{
      navigation_UpdatePosition(0,-15);
    }
    if(obj_side == RIGHT){drive_TurnLeft(90);}
    else if (obj_side == LEFT){drive_TurnRight(90);}
  }
}

void navigation_InitNavigation(){
  pos.x = 60;
  pos.y = 27;
  pos.heading = 0;
}

void navigation_UpdatePosition(int x_mov, int y_mov){
  pos.x = pos.x + x_mov;
  pos.y = pos.y + y_mov;
  pos.heading = drive_GetHeading();
}
