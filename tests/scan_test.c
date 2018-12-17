#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "drive.h"
#include "detect.h"
#include "scan.h"

const int SAMPLE_NUM = 1000; 

int main()
{
    
    drive_Init();
    detect_Init();
    scan_TurnRightScan(180, 10);
  
    return 0;
}