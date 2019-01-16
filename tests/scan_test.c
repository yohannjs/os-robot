#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "drive.h"
#include "detect.h"
#include "scan.h"
#include "navigate.h"

int main(int argc, char **argv)
{    
    if (argc == 1)
    { 
      int samples[360];
      int template[360];
      scan_LoadSamples("samples/samples10.txt", samples);
      scan_LoadSamples("samples/template01.txt", template);
      
      int heading;
      int distance;
      printf("samples[0] = %d\n", samples[0]);
      printf("template[0] = %d\n", template[0]); 
      scan_FindBall(samples, template, &heading, &distance);
      
      printf("Heading: %d\nDistance: %d\n", heading, distance);
    } 
    else if (argc == 2) 
    {

        drive_Init();
        detect_Init();
        navigation_GoToScanPosition(MIDDLE, UP);
        sleep(3);
        int samples[360];
        scan_Scan360(samples);
        scan_WriteSamplesToFile( samples, argv[1] );
    }
    else
      printf("lol nope\n");
    return 0;
}


