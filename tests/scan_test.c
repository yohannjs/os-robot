#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "drive.h"
#include "detect.h"
#include "scan.h"
#include "navigate.h"

int main(int argc, char **argv)
{
    drive_Init();
    detect_Init();
    navigation_GoToScanPosition(MIDDLE, UP);
    sleep(5);
    
    if (argc == 1)
    { 
      int samples[360];
      int template[360];
      scan_LoadSamples("samples006.txt", samples);
      scan_LoadSamples("samples001.txt", template);
      
      int heading;
      int distance; 
      scan_FindBall(samples, template, &heading, &distance);
      
      printf("Heading: %d\nDistance: %d\n", heading, distance);
    } 
    else
      printf("lol nope\n");
    return 0;
}
