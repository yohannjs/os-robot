#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
//#include "queue.h"

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "drive.h"

#define DEG_TO_LIN 2.5
#define RIGHT_PORT 67
#define LEFT_PORT 68

static uint8_t rsn;
static uint8_t lsn;
static uint8_t lr_sn[3];
static int max_speed;
static uint8_t gyro_sn;

void drive_Init(){
  drive_InitTachos();
  drive_SensorInit();
  lr_sn[0] = rsn;
  lr_sn[1] = lsn;
  lr_sn[2] = DESC_LIMIT;
}

int drive_InitTachos(){
  if ( ev3_init() == -1 ){
    printf("could not initialize robot\n");
    return ( 1 );
  }
  while ( ev3_tacho_init() < 1 ){
    sleep( 1000 );
    printf("looking for taco\n");
  }
  if (ev3_search_tacho_plugged_in( RIGHT_PORT,0 , &rsn, 0 )){
    get_tacho_max_speed( rsn, &max_speed );
    set_tacho_stop_action_inx(rsn, TACHO_HOLD);
    set_tacho_ramp_up_sp( rsn, 100 );
    set_tacho_ramp_down_sp( rsn, 100 );
    printf("found motor connected to port: %d\n", RIGHT_PORT);
  }
  if (ev3_search_tacho_plugged_in(LEFT_PORT, 0, &lsn, 0 )){
    set_tacho_stop_action_inx(lsn, TACHO_HOLD);
    set_tacho_ramp_up_sp( lsn, 100 );
    set_tacho_ramp_down_sp( lsn, 100 );
    printf("found motor connected to port: %d\n",LEFT_PORT);
  }
  printf( "Tacho is now ready \n" );
  return 0;
}
int drive_MotorStatus(){
  FLAGS_T state_big_motor;
  get_tacho_state_flags   ( lsn, &state_big_motor);
  if(state_big_motor == TACHO_HOLDING){
    return 0;
  }else{
    return 1;
  }
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
  multi_set_tacho_command_inx(lr_sn, TACHO_RUN_TO_REL_POS );
  while(drive_MotorStatus()){
    usleep(100);
  }
}

void drive_BackDistance(int distance){
  drive_GoDistance(-distance);
}

void drive_Turn(int deg){
  //printf("running drive_turn\n");
  int current_pos;
  current_pos = drive_GetGyroValue();
  int end_pos = current_pos+deg;
  bool left = false;
  bool right = false;

  while(current_pos > end_pos +1 || current_pos < end_pos -1){
    //printf("in turning loop\n");
    if (current_pos < end_pos +1 && right == false){
      //printf("running drive_TurnLeftUntilStopped\n");
      drive_Stop();
      drive_TurnRightForever(60);
      right = true;
      left = false;
    }else if (current_pos > end_pos-1 && left == false){
      //printf("running drive_TurnRightUntilStopped\n");
      drive_Stop();
      drive_TurnLeftForever(60);
      left = true;
      right = false;
    }else if(current_pos < end_pos +2 && current_pos > end_pos -2 ){
      //printf("telling tacho to stop\n");
      multi_set_tacho_command_inx(lr_sn, TACHO_STOP );
      left = false;
      right = false;
      //return;
    }

    current_pos = drive_GetGyroValue();
    //printf("current pos =%d\n", current_pos);
  }
  multi_set_tacho_command_inx(lr_sn, TACHO_STOP);
  usleep(500000);
}

void drive_TurnRight(int deg){
  drive_Turn(deg);
}
void drive_TurnLeft(int deg){
  drive_Turn(-deg);
}
//turn desired amount of degrees without gyro. negative deg turns left
void drive_TurnDegrees(int deg, int speed){
  set_tacho_position_sp(rsn, deg * DEG_TO_LIN);
  set_tacho_position_sp(lsn, -deg * DEG_TO_LIN);
  set_tacho_speed_sp(lsn, max_speed * speed/100);
  set_tacho_speed_sp(rsn, max_speed * speed/100);
  multi_set_tacho_command_inx(lr_sn, TACHO_RUN_TO_REL_POS);
  while(drive_MotorStatus()){
    usleep(100000);
  }
}

void drive_TurnLeftForever(int speed){
  set_tacho_speed_sp( rsn, -max_speed * 1/8 * speed/100);
  set_tacho_speed_sp( lsn, max_speed * 1/8 * speed/100);

  multi_set_tacho_command_inx(lr_sn, TACHO_RUN_FOREVER );
}

void drive_TurnRightForever(int speed){
  set_tacho_speed_sp( rsn, (int)(max_speed * 1/8 * speed/100));
  set_tacho_speed_sp( lsn, (int)(-max_speed * 1/8 * speed/100));

  multi_set_tacho_command_inx(lr_sn, TACHO_RUN_FOREVER);
}


void drive_GoForward(){
  set_tacho_speed_sp( rsn, max_speed * 1 / 6 );
  set_tacho_speed_sp( lsn, max_speed * 1 / 6 );

  multi_set_tacho_command_inx(lr_sn, TACHO_RUN_FOREVER);
}

void drive_GoBackward(){
  set_tacho_speed_sp( rsn, -max_speed * 1 / 6 );
  set_tacho_speed_sp( lsn, -max_speed * 1 / 6 );

  multi_set_tacho_command_inx(lr_sn, TACHO_RUN_FOREVER );
}

void drive_Stop(){
  multi_set_tacho_command_inx(lr_sn, TACHO_STOP);
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
    //printf("gyro value: %d\n", val);
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
  //printf("getHeading called, heading: %d\n", heading);
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
  if(to_turn > 180){
    to_turn = to_turn - 360;
  }
  //printf("turning %d, degrees\n", to_turn);
  drive_Turn(to_turn);
}
