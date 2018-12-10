#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include <unistd.h>
#include "ev3_sensor.h"
#include "drive.h"
#include <math.h>

uint8_t rsn;
uint8_t lsn;
int right_port = 67;
int left_port = 68;
int max_speed;

uint8_t gyro_sn;
//should maybe use a mutex for motors, if they are called by message a queue needs to be made.

/*
void drive_loop(){
  drive_InitTachos();
  drive_SensorInit();
  while(1){

  }
}*/


int drive_InitTachos(){
  if ( ev3_init() == -1 ){
    printf("could not initialize robot\n");
    return ( 1 );
  }
  while ( ev3_tacho_init() < 1 ){
    sleep( 1000 );
    printf("looking for taco\n");
  }
  if (ev3_search_tacho_plugged_in( right_port,0 , &rsn, 0 )){
    get_tacho_max_speed( rsn, &max_speed );
    set_tacho_stop_action_inx(rsn, TACHO_HOLD);
    set_tacho_ramp_up_sp( rsn, 10 );
    set_tacho_ramp_down_sp( rsn, 10 );
    printf("found motor connected to port: %d\n", right_port);
  }
  if (ev3_search_tacho_plugged_in(left_port, 0, &lsn, 0 )){
    set_tacho_stop_action_inx(lsn, TACHO_HOLD);
    set_tacho_ramp_up_sp( lsn, 10 );
    set_tacho_ramp_down_sp( lsn, 10 );
    printf("found motor connected to port: %d\n",left_port);
  }
  printf( "Tacho is now ready \n" );
  return 0;
}

void drive_GoDistance(int distance){
  double wheel_r = 2.7;
  double dist_per_degree = (2*wheel_r*3.14159)/360;
  double turn_degrees = distance / dist_per_degree;
  int turn_degrees_int = (int) turn_degrees;
  set_tacho_position_sp(lsn, turn_degrees_int);
  set_tacho_position_sp(rsn, turn_degrees_int);
  printf("turning wheels %d degrees\n", turn_degrees_int);
  set_tacho_speed_sp( rsn, max_speed * 1 / 3 );
  set_tacho_speed_sp( lsn, max_speed * 1 / 3 );
  set_tacho_command_inx(lsn, TACHO_RUN_TO_REL_POS);
  set_tacho_command_inx(rsn, TACHO_RUN_TO_REL_POS);
}

void drive_BackDistance(int distance){
  drive_GoDistance(-distance);
}

void drive_Turn(int deg, double speed_ratio){
  printf("running drive_turn\n");
  int current_pos;
  current_pos = drive_GetGyroValue();
  int end_pos = current_pos+deg;
  bool left = false;
  bool right = false;

  while(current_pos > end_pos +3 || current_pos < end_pos -3){
    printf("in turning loop\n");
    if (current_pos < end_pos +2 && right == false){
      printf("running drive_TurnLeftUntilStopped\n");
      drive_TurnLeftUntilStopped(speed_ratio);
      right = true;
      left = false;
    }else if (current_pos > end_pos-2 && left == false){
      printf("running drive_TurnRightUntilStopped\n");
      drive_TurnRightUntilStopped(speed_ratio);
      left = true;
      right = false;
    }else if(current_pos < end_pos +2 && current_pos > end_pos -2 ){
      printf("telling tacho to stop\n");
      set_tacho_command_inx( rsn, TACHO_STOP);
      set_tacho_command_inx( lsn, TACHO_STOP);
      left = false;
      right = false;
      //return;
    }

    current_pos = drive_GetGyroValue();
  }
  set_tacho_command_inx( rsn, TACHO_STOP);
  set_tacho_command_inx( lsn, TACHO_STOP);
  sleep(1);
}
void drive_ScanTurn(){
  drive_Turn(360, 0.15);
}
void drive_TurnRight(int deg){
  drive_Turn(deg, 0.25);
}
void drive_TurnLeft(int deg){
  drive_Turn(-deg, 0.25);
}

void drive_TurnLeftUntilStopped(double speed_ratio){
  set_tacho_speed_sp( rsn, max_speed * speed_ratio);
  set_tacho_speed_sp( lsn, -max_speed * speed_ratio);

  set_tacho_command_inx( rsn, TACHO_RUN_FOREVER);
  set_tacho_command_inx( lsn, TACHO_RUN_FOREVER);
}

void drive_TurnRightUntilStopped(double speed_ratio){
  set_tacho_speed_sp( rsn, -max_speed * speed_ratio);
  set_tacho_speed_sp( lsn, max_speed * speed_ratio);
  printf("in turnrightUntilstopped\n");
  set_tacho_command_inx( rsn, TACHO_RUN_FOREVER);
  set_tacho_command_inx( lsn, TACHO_RUN_FOREVER);
}



void drive_GoForward(){
  set_tacho_speed_sp( rsn, max_speed * 2 / 3 );
  set_tacho_speed_sp( lsn, max_speed * 2 / 3 );

  set_tacho_command_inx( rsn, TACHO_RUN_FOREVER);
  set_tacho_command_inx( lsn, TACHO_RUN_FOREVER);
}

void drive_GoBackward(){
  set_tacho_speed_sp( rsn, -max_speed * 2 / 3 );
  set_tacho_speed_sp( lsn, -max_speed * 2 / 3 );

  set_tacho_command_inx( rsn, TACHO_RUN_FOREVER);
  set_tacho_command_inx( lsn, TACHO_RUN_FOREVER);
}

void drive_Stop(){
  set_tacho_command_inx( rsn, TACHO_STOP);
  set_tacho_command_inx( lsn, TACHO_STOP);
}

void drive_SensorInit(){
  int initResult;
  initResult = ev3_sensor_init();
  if(initResult == 0){
   printf("No sensors connected\n");
 }else if(initResult == -1){
   printf("Error when initializing sensors\n");
 }else{
   printf("Initialized sensors. %d sensors connected\n", initResult );
 }
 if (ev3_search_sensor(LEGO_EV3_GYRO, &gyro_sn, 0)){
   set_sensor_mode(gyro_sn, "GYRO-RATE");
   set_sensor_mode(gyro_sn, "GYRO-ANG");
   printf("Gyro sensor detected, set in angle detection mode.\n");
 }else {
   printf("No gyroscope found\n");
 }
}

int drive_GetGyroValue(){
  int val;
  if (ev3_search_sensor( LEGO_EV3_GYRO, &gyro_sn, 0 )){
    get_sensor_value( 0, gyro_sn, &val);
    printf("gyro value: %d\n", val);
  }
  return val;
}
//gyroscope can return negative heading, need to take this into account.
int drive_GetHeading(){
  int heading;
  int gyro_val;
  gyro_val = drive_GetGyroValue();
  if (gyro_val < 0){
    heading = (gyro_val % 360) + 360;
  }else{
    heading = gyro_val % 360;
  }
  printf("getHeading called, heading: %d\n", heading);
  return heading;
}

void drive_ResetGyro(){
  set_sensor_mode(gyro_sn, "GYRO-RATE");
  set_sensor_mode(gyro_sn, "GYRO-ANG");
}

void drive_SetHeading(int desired_heading){
  int current_heading;
  int to_turn;
  current_heading = drive_GetHeading();
  to_turn = desired_heading-current_heading;
  printf("turning %d, degrees\n", to_turn);
  drive_Turn(to_turn, 1/4);
}
