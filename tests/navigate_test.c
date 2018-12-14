#include "navigate.h"
#include <stdio.h>

int main(){

drive_Init();
navigation_GoToScanPosition(DIAGONAL, LEFT_DIAGONAL);
printf("Went to scan position\n");
navigation_MoveToBall(10, 55);
printf("pretended to find ball here\n");
sleep(4);
navigation_ReturnToScanPosition();
printf("success, i am good. returning\n");
navigation_ReturnFromScanPosition();
sleep(2);

return 0;
}
