#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// #include "navigate.h"
// #include "drive.h"
// #include "claw.h"
#include "detect.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )

float distance;
char *color;

int main(){
  detect_Init();
  
  while(1){
    distance = detect_GetDistance();
    printf("Distance to the wall is %f \n", distance);
    sleep(2);
    if(detect_OnLine() == true)
    {
      color = "BLACK";
    } else 
    {
      color = "NOT BLACK";
    }
    printf("Colour detected is %s \n", color);
  }
  return 0;
}