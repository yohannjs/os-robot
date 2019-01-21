#include <stdio.h>
#include <unistd.h>
#include "utils.h"
#include "claw.h"

const char *mn = "  TEST  ";

int main(){
  if(claw_Init())
  {
    utils_Err(mn, "Could not initialize claw");
    return -1;
  } 

  //utils_Sleep(500); 
  if (claw_TakeBall())
  {

    //utils_Sleep(500);
    printf("Ball caught \n");
    utils_Sleep(1000);
    claw_Throw();
    // claw_Drop();
    // sleep(1);
    // claw_Reset();
  } else {
    printf("Ball not caught \n");
  }
  
  // claw_Drop();
  // claw_Reset();
  return 0;
}
