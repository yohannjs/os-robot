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
        int heading;
        int distance;
        //navigation_GoToScanPosition(MIDDLE, UP);
        //sleep(3);
        int samples[360];
        int threshold = 200;
        //scan_Scan360( samples, 3 );
        printf("Done with scan, moving to file \n");
        printf(argv[1]);
        //scan_FindBall2(samples, threshold, &heading, &distance);
        scan_WriteSamplesToFile( samples, argv[1] );
        //navigation_MoveToBall(distance, heading);
        //int adjustDistance;
        //detect_GetDistance();
        //navigation_AdjustBallDistance(adjustDistance);

    }
    else
      printf("lol nope\n");
    return 0;
}


