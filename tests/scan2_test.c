#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "drive.h"
#include "detect.h"
#include "scan.h"
// #include "navigate.h"


int main(int argc, char **argv)
{  
    drive_Init();
    detect_Init(); 
    int samples[360];
    int template[360];
    int heading;
    int distance;

    if (argc == 1)
    { 
        scan_LoadSamples("samples/samples10.txt", samples);
        scan_LoadSamples("samples/template01.txt", template);
        printf("samples[0] = %d\n", samples[0]);
        printf("template[0] = %d\n", template[0]); 
        scan_FindBall(samples, template, &heading, &distance);
        printf("Heading: %d\nDistance: %d\n", heading, distance);
    } 
    else if (argc == 2) 
    {
        int threshold = 200;
        scan_Scan360( samples, 3 );
        printf("Done with scan, moving to file \n");
        // printf(argv[1]);
        scan_FindBall2(samples, threshold, &heading, &distance);
        scan_WriteSamplesToFile( samples, argv[1] );
        printf("Heading ball: %d \n", heading);
        printf("Distance ball: %d \n", distance);

    }
    else
    {
        printf("lol nope\n");
    }
    return 0;
}


