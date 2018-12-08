#include <stdio.h>
#include "claw.h"

int main(){
    if(claw_Init() == 0)
    {
      printf('Initializing claw');
    } else {
      return -1;
    }
    claw_Grab();
    claw_Throw();
    return 0;
}
