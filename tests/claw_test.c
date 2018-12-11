#include "../src/interfaces/claw.h"

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
