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
#include "utils.h"

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
    utils_Sleep( 100 );
    printf("looking for taco\n");
  }
  if (ev3_search_tacho_plugged_in( RIGHT_PORT,0 , &rsn, 0 )){
    get_tacho_max_speed( rsn, &max_speed );
    set_tacho_stop_action_inx(rsn, TACHO_HOLD);
    set_tacho_ramp_up_sp( rsn, 1000 );
    set_tacho_ramp_down_sp( rsn, 1000 );
    printf("found motor connected to port: %d\n", RIGHT_PORT);
  }
  if (ev3_search_tacho_plugged_in(LEFT_PORT, 0, &lsn, 0 )){
    set_tacho_stop_action_inx(lsn, TACHO_HOLD);
    set_tacho_ramp_up_sp( lsn, 1000 );
    set_tacho_ramp_down_sp( lsn, 1000 );
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
  if (distance == 0){
    return;
  }
  double wheel_r = 2.7;
  double dist_per_degree = (2*wheel_r*3.14159)/360;
  double turn_degrees = distance / dist_per_degree;
  int turn_degrees_int = (int) turn_degrees;
  set_tacho_position_sp(lsn, turn_degrees_int);
  set_tacho_position_sp(rsn, turn_degrees_int);
  // printf("turning wheels %d degrees\n", turn_degrees_int);
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
  printf("[Turn] Running drive_turn\n");
  int current_pos = drive_GetHeading();
  int end_pos = current_pos + deg;
  bool left = false;
  bool right = false;
  current_pos = drive_GetGyroValue();
  while(current_pos > end_pos +1 || current_pos < end_pos -1)
  {
    // printf("[Turn] In turning loop\n");
    if (current_pos < end_pos +1 && right == false)
    {
      printf("[Turn] Running drive_TurnRightUntilStopped\n");
      drive_Stop();
      drive_TurnRightForever(60);
      right = true;
      left = false;
    }
    else if (current_pos > end_pos-1 && left == false)
    {
      printf("[Turn] Running drive_TurnLeftUntilStopped\n");
      drive_Stop();
      drive_TurnLeftForever(60);
      left = true;
      right = false;
    }
    else if (current_pos < end_pos +2 && current_pos > end_pos -2 )
    {
      drive_Stop();
      printf("[Turn] Telling tacho to stop\n");
      // multi_set_tacho_command_inx(lr_sn, TACHO_STOP );
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
  set_tacho_speed_sp( rsn, max_speed * 1 / 8 );
  set_tacho_speed_sp( lsn, max_speed * 1 / 8 );

  multi_set_tacho_command_inx(lr_sn, TACHO_RUN_FOREVER);
}

void drive_GoBackward(){
  set_tacho_speed_sp( rsn, -max_speed * 1 / 8 );
  set_tacho_speed_sp( lsn, -max_speed * 1 / 8 );

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
  if (ev3_search_sensor( LEGO_EV3_GYRO, &gyro_sn, 0 ))
  {
    get_sensor_value( 0, gyro_sn, &val);
  }
  return val;
}
// Returns heading as a number between 0 and 360.
int drive_GetHeading(){
  int heading;
  int gyro_val;
  gyro_val = drive_GetGyroValue();
  if (gyro_val < 0)
  {
    heading = (gyro_val % 360) + 360;
  }
  else
  {
    heading = gyro_val % 360;
  }
  return heading;
}

void drive_ResetGyro(){
  set_sensor_mode(gyro_sn, "GYRO-RATE");
  set_sensor_mode(gyro_sn, "GYRO-ANG");
}

void drive_SetHeading(int desired_heading)
{
  // printf("[SetHeadingY] Desired heading: %d \n", desired_heading);
  int current_heading = drive_GetHeading();
  // printf("[SetHeadingY] Current heading: %d \n", current_heading);
  int degrees_to_turn = desired_heading - current_heading;
  char* direction;

  if (abs(degrees_to_turn) <= 1)
  {
    return;
  }

  else if (degrees_to_turn > 180 || (degrees_to_turn < 0 && degrees_to_turn > -181))
  {
    direction = "left";
    if (abs(degrees_to_turn) > 10){
      drive_TurnLeftForever(40);
    }else {
      drive_TurnLeftForever(20);
    }
    // printf("[SetHeadingY] Turning left \n");
  }
  else
  {
    direction = "right";
    if (abs(degrees_to_turn) > 10){
      drive_TurnRightForever(40);
    }else {
      drive_TurnRightForever(20);
    }
    // printf("[SetHeadingY] Turning right \n ");
  }

  while (abs(current_heading - desired_heading) > 1)
  {
    // printf("[SetHeadingY] desired heading - current heading = %d \n", desired_heading - current_heading);
    current_heading = drive_GetHeading();
    if (abs(current_heading -desired_heading) <= 10){
      if (direction =="left"){
        drive_TurnLeftForever(20);
      }else{
        drive_TurnRightForever(20);
      }
    }
    if (abs(current_heading - desired_heading) <= 1)
    {
      break;
    }
    // usleep(5000);
  }
  drive_Stop();
  usleep(500000);
}
