#include "drive.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "navigate.h"
#include "queue.h"
#include "detect.h"
#include <mqueue.h>
#include <pthread.h>


static const int START_X = 60;
static const int START_Y = 27;
//static const int Y_SEARCH_OFFSET = 20;
static const int START_THROWLINE_OFFSET = 33;
//static const int X_SERCHPOINT_OFFSET = 30;
//static const int DIAGONAL_SEARCHPOINT_ANGLE = 40;
//static const int DIAGONAL_SEARCHPOINT_DISTANCE = 40;
static searchpoint_distance current_robot_distance;
static direction current_robot_heading;
static int ball_distance = 0;
static int ball_direction = 0;

void navigation_Init(){
  drive_Init();
}

/*
  char* queue_name = "/queue_name";
  mqd_t *queue_descriptor;
  if (queue_Create(queue_name, queue_descriptor)){
    printf("Error when making message queue\n");
  }
  pthread_t drive_thread;
  if(pthread_create(&drive_thread, NULL, drive_loop, &queue_descriptor)){
    printf("Could not make thread for drive module loop\n");
  }

}
*/

void navigation_GoToScanPosition(searchpoint_distance distance, direction direction){
  drive_SetHeading(direction);
  sleep(5);
  drive_GoDistance(distance);
  sleep(5);
  current_robot_heading = direction;
  current_robot_distance = distance;
}

void navigation_ReturnFromScanPosition(){
  drive_SetHeading(current_robot_heading);
  sleep(5);
  drive_BackDistance(current_robot_distance);
  sleep(5);
  drive_SetHeading(0);
  sleep(5);
}
//should this also register objects somewhere?
void navigation_MoveToBall(int distance_to_ball, int ball_heading){
  ball_distance = distance_to_ball-13;
  ball_direction = ball_heading;
  drive_SetHeading(ball_heading);
  drive_GoDistance(ball_distance);
}

void navigation_ReturnToScanPosition(){
  drive_BackDistance(ball_distance);
  sleep(5);
  //drive_Turn(-ball_direction);
  //sleep(2);
}

void navigation_GoToShootingPosition(){
  drive_GoForward(20);
  sleep(2);
  bool is_on_line = false;
  drive_GoForward();
  while(is_on_line == false){
    is_on_line = detect_OnLine();
  }
  drive_Stop();
}
void navigation_ReturnAfterThrow(){
  drive_BackDistance(START_THROWLINE_OFFSET);
}
/*
void navigation_GoToStart(){
  //navigation_GoToPosition(60,27);
}
*/

void navigation_RecalibrateGyro(){
  drive_GoDistance(70);
  sleep(1);
  drive_ResetGyro();
  drive_BackDistance(61);
}
