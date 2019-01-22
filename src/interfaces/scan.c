#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "drive.h"
#include "detect.h"
#include "utils.h"

#define SCAN_MAX

static const char *mn = "  SCAN  ";

int scan_Scan360(int* samples)
{
  //FILE* f;
  //f = fopen("samples.txt", "w");
  int heading = drive_GetHeading();
  //int new_samples[360];
  drive_TurnRightForever(30);

  // Set all indices in sample array to invalid value
  for (int i=0; i<360; i++) 
  {
    samples[i] = -1;
  }

  for (int i=0; i<360; i++)
  {
    int current_heading = heading;
    int sum = 0;
    int num = 0;
    do {
      heading = drive_GetHeading();
      sum += detect_GetDistance();
      num++;
      usleep(10 * 1000);
    } while (current_heading == heading);
    samples[current_heading] = sum / num;
  }

  drive_Stop();

  for (int i=0; i<360; i++)
  {
    if (samples[i] < 0)
    {
      utils_Err(mn, "Invalid distances in scan");
      return 1;
    }
  }
  return 0;
}

int scan_WriteSamplesToFile(int* samples, char *file_name)
{
  FILE *f;
  f = fopen(file_name, "w");
  for (int i=0; i<360; i++)
  {
    fprintf(f, "%d\n", samples[i]);
  }
  printf("[  SCAN  ] Samples written to file %s\n", file_name);
  fclose(f);

  return 0;
}

int scan_LoadSamples(char *file_name, int *samples)
{
  FILE *f;
  f = fopen(file_name, "r");
  if (!f)
  {
    printf("[  SCAN  ] Error, %s not found\n", file_name);
    return 1;
  }
  //int loaded_samples[360];
  for (int i=0; i<360; i++)
  {
    int val;
    fscanf(f, "%d", &val);
    // printf("%d\n", val);
    samples[i] = val;
  }
  fclose(f);
  //samples = loaded_samples;
  return 0;
}

int scan_FindBall2(int* samples, int threshold, int *head, int *dist)
{
  int min_length = 15;
  int start_heading;
  int end_heading = 0;
  *head = 0;
  *dist = 0;
  for (int i=0; i<360; i++)
  {
    start_heading = i;
    while (samples[i] <= threshold)
    {
      end_heading = i;
      i++;
    }
    if (end_heading > start_heading + min_length)
    {
      int length = end_heading - start_heading;
      *head = start_heading + length / 2;
      *dist = samples[*head];

      printf("Found ball at heading: %d and distance: %d\n", *head, *dist);
      // return 0;
    }
  }
  if (end_heading == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
