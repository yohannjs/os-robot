#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "drive.h"
#include "detect.h"

int scan_TurnRightScan(int degrees, int speed)
{
  FILE* f;
  f = fopen("samples.txt", "w");
  drive_TurnDegrees(degrees, speed);
  int heading;
  while(1)
  {
    heading = drive_GetHeading();
    fprintf(f, "%d\t%d\n", heading, detect_GetDistance());
    usleep(10 * 1000);
  }
  fclose(f);
  return 0;
}
