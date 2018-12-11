
#include <stdio.h>
#include <stdlib.h>
#include "lib/ev3.h"
#include "lib/ev3_port.h"
#include "lib/ev3_tacho.h"
#include <unistd.h>
#include "lib/ev3_sensor.h"
#include "claw.h"
#include "claw.c"

#define Sleep( msec ) usleep(( msec ) * 1000 )

int main(){
  if(claw_Init() == 0)
  {
    printf("Initialized claw \n");
  } else return -1;
  sleep(1);
  claw_Throw();
  sleep(1);
  /*sleep(5);
  get_tacho_position(big_motor, &big_motor_pos);
  printf("Position: %d \n",big_motor_pos); */
  //sleep(5);
  claw_Lower();
  sleep(1);
  claw_Grab();
  bool hold = claw_HoldsBall();
  printf("Hold value is %d \n", hold);
  sleep(3);
  claw_Throw();
  
  
  return 0;
}
