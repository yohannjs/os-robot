#include "navigate.h"
#include <stdio.h>

int main(){

navigation_Init();
navigation_GoToScanPosition(SOUTH_EAST);
printf("Went to scan position\n");
navigation_MoveToBall(10, 55);
printf("pretended to find ball here\n");

navigation_ReturnToScanPosition();
printf("success, i am good. returning\n");
navigation_ReturnFromScanPosition();


return 0;
}
