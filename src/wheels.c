
#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include <unistd.h>
#include "ev3_sensor.h"
#include "wheels.h"
#include "gyroscope.h"

uint8_t rsn;
uint8_t lsn;
int right_port = 66;
int left_port = 67;
int max_speed;

void sensorInit();
int get_gyro_value(int val);
uint8_t gyro_sn;

int main(){
  //initializing motors and gyroscope
  initTachos();
  sensorInit();
  //setting the max_speed variable
  get_tacho_max_speed( rsn, &max_speed );
  //running funcitons
  gyroTurn(90);

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
    set_tacho_stop_action_inx(rsn, TACHO_BRAKE);
    printf("found motor connected to port: %d\n", right_port);
  }
  if (ev3_search_tacho_plugged_in(left_port, 0, &lsn, 0 )){
    set_tacho_stop_action_inx(lsn, TACHO_BRAKE);
    printf("found motor connected to port: %d\n",left_port);
  }

  printf( "Tacho is now awake and ready \n" );
  return 0;
}


void turnDegRight(int deg){
  printf( "run to relative position...\n" );
  set_tacho_speed_sp( rsn, max_speed / 2 );
  set_tacho_ramp_up_sp( rsn, 0 );
  set_tacho_ramp_down_sp( rsn, 0 );
  set_tacho_position_sp( rsn, deg );

  set_tacho_speed_sp( lsn, max_speed / 2 );
  set_tacho_ramp_up_sp( lsn, 0 );
  set_tacho_ramp_down_sp( lsn, 0 );
  set_tacho_position_sp( lsn, -deg );

  set_tacho_command_inx( rsn, TACHO_RUN_TO_REL_POS );
  set_tacho_command_inx( lsn, TACHO_RUN_TO_REL_POS );

}

void gyroTurn(int deg){
  int current_pos;
  current_pos = get_gyro_value();
  int end_pos = current_pos+deg;
  while(current_pos > end_pos +3 || current_pos < end_pos -3){
    if(end_pos < current_pos){
      turnRight();
    }else{
      turnLeft();
    }
    current_pos = get_gyro_value();
  }
}

void turnLeft(){
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
void turnRight(){
  set_tacho_speed_sp( rsn, -max_speed * 2 / 3 );
  set_tacho_speed_sp( lsn, max_speed * 2 / 3 );

  set_tacho_time_sp( lsn, 20 );
  set_tacho_ramp_up_sp( lsn, 5 );
  set_tacho_ramp_down_sp( lsn, 5 );
  set_tacho_time_sp( rsn, 20 );
  set_tacho_ramp_up_sp( rsn, 5 );
  set_tacho_ramp_down_sp( rsn, 5 );

  set_tacho_command_inx( rsn, TACHO_RUN_TIMED );
  set_tacho_command_inx( lsn, TACHO_RUN_TIMED );
}                                                                                                                                       33,0-1        Bot

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
 }else {
   printf("No gyroscope found\n");
 }
}

int get_gyro_value(){
  //uint8_t gyro_sn;
  int val;
  if (ev3_search_sensor( LEGO_EV3_GYRO, &gyro_sn, 0 )){
    get_sensor_value( 0, gyro_sn, &val);
    printf("gyro value: %d\n", val);
  }
  return val;
}
