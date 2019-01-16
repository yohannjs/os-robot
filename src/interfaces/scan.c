#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "drive.h"
#include "detect.h"

int scan_Scan360(int* samples, int speed)
{
  //FILE* f;
  //f = fopen("samples.txt", "w");
  int heading = drive_GetHeading();
  //int new_samples[360];
  drive_TurnDegrees(365, speed);
    
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
  //samples = new_samples;
  //int heading;
  //while(get)
  //{
  //  heading = drive_GetHeading();
  //  fprintf(f, "%d\t%d\n", heading, detect_GetDistance());
  //  usleep(10 * 1000);
  //}
  //fclose(f);
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

int scan_TurnRightScan(int degrees, int speed)
{
  FILE* f;
  f = fopen("samples.txt", "w");

  int NUM_SAMPLES;
  drive_TurnRightForever(speed);
  int heading;
  while(1)
  {
    heading = drive_GetHeading();
    if (heading >= degrees) break;
    fprintf(f, "%d\t%d\n", heading, detect_GetDistance());
    NUM_SAMPLES++;
    usleep(10 * 1000);
  }
  fclose(f);
  drive_Stop();
  return NUM_SAMPLES;
}

int scan_FindBall(int* samples, int* template, int *head, int *dist)
{
  int threshold = 100;
  int min_length = 20;
  int diff[360];
  
  int start_heading;
  int end_heading = 0;
  for (int i=0; i<360; i++)
  {
    diff[i] = template[i] - samples[i];
    printf("Diff[%d] = %d\n", i, diff[i]);
    start_heading = i;
    while (diff[i] >= threshold)
    {
      end_heading = i;
      i++;
      diff[i] = template[i] - samples[i];
      printf("Diff[%d] = %d\n", i, diff[i]);
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

int scan_FindBallHeading(int NUM_SAMPLES, int* head, int* dist){
  int heading[1500];// = {0};
  int distance[1500];// = {0};
  FILE* f;
  f = fopen("samples.txt", "r"); // INSERT CORRECT FILE NAME HERE
  if(!f){
    printf("Error, samples.txt not found \n");
    return -1;
  }
  int dista;
  for (int i = 0; i < NUM_SAMPLES; i++){
    fscanf(f, "%d\t%d", &heading[i], &dista);
    if(*dist > 500){
      distance[i] = 500;
    } else{
      distance[i] = dista;
    }
  }
  int minimum_distance = distance[0];
  int index_counter;
  int minimum_heading;
  for (int k = 0; k < NUM_SAMPLES; k++){
    if(distance[k] < minimum_distance && distance[k] > 0){
      minimum_distance = distance[k];
      index_counter = k;
    }
  }
  printf("distance to ball = %d \n associated heading = %d \n", minimum_distance, index_counter);
  *head = index_counter;
  *dist = minimum_distance; 
  fclose(f);
  return 0;
}

int scan_FindBall2(int* samples, int threshold, int *head, int *dist)
{
  int min_length = 20; 
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
