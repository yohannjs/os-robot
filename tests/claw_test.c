#include <stdio.h>
#include <unistd.h>

#include "claw.h"

int main(){
  if(claw_Init() == 0)
  {
    printf("Initialized claw \n");
  } else return -1;
  /*
  if (claw_TakeBall()==1)
  {
    printf("Ball caught \n");
    claw_Drop();
  }
  */
  claw_Drop();
  claw_Reset();
  return 0;
}
