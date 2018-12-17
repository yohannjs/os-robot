#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "drive.h"
#include "detect.h"
#include "scan.h"
#include "navigate.h"

int main()
{
    
    drive_Init();
    detect_Init();
    navigation_GoToScanPosition(MIDDLE, UP);
    sleep(5);
    scan_TurnRightScan(359, 15);
  
    return 0;
}
