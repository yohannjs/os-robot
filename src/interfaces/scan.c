#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "drive.h"
#include "detect.h"

int scan_TurnRightScan(int degrees, int speed)
{
  int heading;
  int distance;

  FILE* f;
  f = fopen("samples.txt", "w");

  drive_TurnRightForever(speed);
    
  while(1)
  {
    heading = drive_GetHeading();
    distance = detect_GetDistance();
    if ( heading >= degrees ) break;
    fprintf(f, "%d\t%d\n", drive_GetHeading(), detect_GetDistance());
    usleep(10 * 1000);
  }
  fclose(f);
  drive_Stop();
  return 0;
}
