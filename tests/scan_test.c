#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "drive.h"
#include "detect.h"
#include "scan.h"

int main()
{
    
    drive_Init();
    detect_Init();
    scan_TurnRightScan(360, 10);
  
    return 0;
}
