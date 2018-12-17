#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "drive.h"
#include "detect.h"

int scan_ScanDegrees(int degrees, int speed)
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
