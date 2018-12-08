
#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include <unistd.h>
#include "ev3_sensor.h"
#include "drive.h"

uint8_t rsn;
uint8_t lsn;
int right_port = 65;
int left_port = 68;
int max_speed;

uint8_t gyro_sn;

int main(){
  //initializing motors and gyroscope
  initTachos();
  sensorInit();
  //setting the max_speed variable
  get_tacho_max_speed( rsn, &max_speed );
  //running funcitons
  gyroTurn(90);
  sleep(3);
  forward();
  sleep(2);
  stop();
  backward();
  sleep(3);
  stop();
  ev3_uninit();
  return 0;
}
int initTachos(){
  if ( ev3_init() == -1 ){
    printf("could not initialize robot\n");
    return ( 1 );
  }
  while ( ev3_tacho_init() < 1 ){
    Sleep( 1000 );
    printf("looking for taco\n");
  }
  if (ev3_search_tacho_plugged_in( right_port,0 , &rsn, 0 )){
    set_tacho_stop_action_inx(rsn, TACHO_HOLD);
    set_tacho_ramp_up_sp( rsn, 5 );
    set_tacho_ramp_down_sp( rsn, 5 );
    printf("found motor connected to port: %d\n", right_port);
  }
  if (ev3_search_tacho_plugged_in(left_port, 0, &lsn, 0 )){
    set_tacho_stop_action_inx(lsn, TACHO_HOLD);
    set_tacho_ramp_up_sp( lsn, 5 );
    set_tacho_ramp_down_sp( lsn, 5 );
    printf("found motor connected to port: %d\n",left_port);
  }
  printf( "Tacho is now ready \n" );
  return 0;
}

void gyroTurn(int deg){
  int current_pos;
  current_pos = get_gyro_value();
  int end_pos = current_pos+deg;
  bool left = false;
  bool right = false;

  while(current_pos > end_pos +3 || current_pos < end_pos -3){

    if (current_pos < end_pos +2 && right == false){
      turnLeft();
      right = true;
      left = false;
    }else if (current_pos > end_pos-2 && left == false){
      turnRight();
      left = true;
      right = false;
    }else if(current_pos < end_pos +2 && current_pos > end_pos -2 ){
      set_tacho_command_inx( rsn, TACHO_STOP);
      set_tacho_command_inx( lsn, TACHO_STOP);
      left = false;
      right = false;
      //return;
    }

    current_pos = get_gyro_value();
  }
  set_tacho_command_inx( rsn, TACHO_STOP);
  set_tacho_command_inx( lsn, TACHO_STOP);
  Sleep(200);
}

void turnLeft(){
  set_tacho_speed_sp( rsn, max_speed * 1 / 3 );
  set_tacho_speed_sp( lsn, -max_speed * 1 / 3 );

  set_tacho_command_inx( rsn, TACHO_RUN_FOREVER);
  set_tacho_command_inx( lsn, TACHO_RUN_FOREVER);
}

void turnRight(){
  set_tacho_speed_sp( rsn, -max_speed * 1 / 3 );
  set_tacho_speed_sp( lsn, max_speed * 1 / 3 );

  set_tacho_command_inx( rsn, TACHO_RUN_FOREVER);
  set_tacho_command_inx( lsn, TACHO_RUN_FOREVER);
}

void forward(){
  set_tacho_speed_sp( rsn, max_speed * 2 / 3 );
  set_tacho_speed_sp( lsn, max_speed * 2 / 3 );

  set_tacho_command_inx( rsn, TACHO_RUN_FOREVER);
  set_tacho_command_inx( lsn, TACHO_RUN_FOREVER);
}

void backward(){
  set_tacho_speed_sp( rsn, -max_speed * 2 / 3 );
  set_tacho_speed_sp( lsn, -max_speed * 2 / 3 );

  set_tacho_command_inx( rsn, TACHO_RUN_FOREVER);
  set_tacho_command_inx( lsn, TACHO_RUN_FOREVER);
}

void stop(){
  set_tacho_command_inx( rsn, TACHO_STOP);
  set_tacho_command_inx( lsn, TACHO_STOP);
}

void sensorInit(){
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
   set_sensor_mode(gyro_sn, "GYRO-ANG");
   printf("Gyro sensor detected, set in angle detection mode.\n");
 } else if(ev3_search_sensor(LEGO_EV3_US, &sonar_sn, 0)){
   //set_sensor_mode(gyro_sn, "GYRO-ANG");
   printf("Sonar detected.\n");
 }else {
   printf("No gyroscope found\n");
 }
}

int get_gyro_value(){
  int val;
  if (ev3_search_sensor( LEGO_EV3_GYRO, &gyro_sn, 0 )){
    get_sensor_value( 0, gyro_sn, &val);
    //printf("gyro value: %d\n", val);
  }
  return val;
}

int getApproxHeading(){
  int heading;
  int gyro_val;
  gyro_val = get_gyro_value();
  heading = gyro_val % 360;
  return heading;
}

void turnLeftInterval(){
  set_tacho_speed_sp( rsn, max_speed * 2 / 3 );
  set_tacho_speed_sp( lsn, -max_speed * 2 / 3 );

  set_tacho_time_sp( lsn, 20 );
  set_tacho_ramp_up_sp( lsn, 5 );
  set_tacho_ramp_down_sp( lsn, 5 );
  set_tacho_time_sp( rsn, 20 );
  set_tacho_ramp_up_sp( rsn, 5 );
  set_tacho_ramp_down_sp( rsn, 5 );

  set_tacho_command_inx( rsn, TACHO_RUN_TIMED );
  set_tacho_command_inx( lsn, TACHO_RUN_TIMED );
}
void turnRightInterval(){
  set_tacho_speed_sp( rsn, -max_speed * 2 / 3 );
  set_tacho_speed_sp( lsn, max_speed * 2 / 3 );

  set_tacho_time_sp( lsn, 20 );
  set_tacho_ramp_up_sp( lsn, 5 );
  set_tacho_ramp_down_sp( lsn, 5 );
  set_tacho_time_sp( rsn, 20 );
  set_tacho_ramp_up_sp( rsn, 5 );
  set_tacho_ramp_down_sp( rsn, 5 );

  set_tacho_command_inx( rsn, TACHO_RUN_TIMED );
  set_tacho_command_inx( lsn, TACHO_RUN_TIMED );}                                                                                                                                       33,0-1        Bot
