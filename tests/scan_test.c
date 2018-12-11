#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "../src/interfaces/drive.c"
#include "../src/interfaces/drive.h"
#include "../src/adapters/detect.h"

const int SAMPLE_NUM = 1000; 

int main()
{
    
    drive_Init();
    detect_Init();
  scan_TurnRightScan(180, 10);
  
    return 0;
}
