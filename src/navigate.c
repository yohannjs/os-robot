#include "drive.h"
#include <stdio.h>
#include <unistd.h>

//Position x goes from 0 to 12, y goes from 0 to 10

struct Position {
   int x;
   int y;
   int off_x;
   int off_y;
   int heading;
} pos;




main(){
//every time robot is done moving, update pos.off_x and pos.off_y with navigation_UpdatePosition.
}

int navigation_MoveOneForward(){
  if (sensors_DistanceToObject > 15){
    drive_GoDistance(10);
    return(0);
  }else{
    //object in front of robot, cannot go there
    return -1;
  }
}

void navigation_GoToPosition(int x, int y){
  if (pos.x > x){
    drive_SetHeading(270);
    usleep(20000);
    drive_GoDistance(off_x);
    while(pos.x != x)
      if(navigation_MoveOneForward())== -1){
        //could not move forward, register object?
        break;
      }else{
        navigation_UpdatePosition(-10,0);
  }
} if (pos.x < x){
      drive.SetHeading(90);
      usleep(20000);
      drive_GoDistance(off_x);
      while(pos.x != x){
        if(navigation_MoveOneForward() == -1){
          //could not move forward, register object?
          break;
        }else{
          navigation_UpdatePosition(10,0);
        }
      }
    }
    if (pos.y > y){
      drive_SetHeading(180);
      usleep(20000);
      drive_GoDistance(off_y);
      while(pos.y != y)
        if(navigation_MoveOneForward())== -1){
          //could not move forward, register object?
          break;
        }else{
          navigation_UpdatePosition(,-10);
    }
  } if (pos.x < x){
        drive.SetHeading(0);
        usleep(20000);
        drive_GoDistance(off_y);
        while(pos.y != y){
          if(navigation_MoveOneForward() == -1){
            //could not move forward, register object?
            break;
          }else{
            navigation_UpdatePosition(0,10);
          }
        }
      }
    if (pos.x != x || pos.y != y){
      //recursive function until complete movement.
      navigation_GoToPosition();
    }
}


void navigation_InitNavigation(){
  pos.x = 5;
  pos.y = 2;
  pos.heading = 0;
  pos.off_x = 5;
  pos.off_y = 2;
}

void navigation_UpdatePosition(int x_mov, int y_mov){
  pos.off_x = pos.off_x + x_mov;
  pos.off_y = pos.off_y + y_mov;
  while(pos.off_x < -10){
    pos.x = pos.x -1;
    pos.off_x = pos.off_x +10;
  }
  while(pos.off_y < -10){
    pos.y = pos.y -1;
    pos.off_y = pos.off_y +10;
  }
  while(pos.off_x > 10){
    pos.x = pos.x +1;
    pos.off_x = pos.off_x -10;
  }
  while(pos.off_y > 10){
    pos.y = pos.y +1;
    pos.off_y = pos.off_y -10;
  }
  pos.heading = drive_GetHeading();
}
