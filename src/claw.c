#include <stdio.h>
#include <stdlib.h>
#include "lib/ev3.h"
#include "lib/ev3_port.h"
#include "lib/ev3_tacho.h"
#include <unistd.h>
#include "lib/ev3_sensor.h"
#include "claw.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )


// big motor parameters
uint8_t big_motor;
int port_big_motor = 66;
int relative_position_big_motor;
int max_speed_big_motor;
FLAGS_T state_big_motor;

// small motor parameters
uint8_t small_motor;
static int port_small_motor = 65;
int relative_position_small_motor;
int max_speed_small_motor; // Might not be neccesary
FLAGS_T state_small_motor;

int big_motor_pos;
int small_motor_pos;


int main(){
  if(claw_Init() == 0)
  {
    printf("Initialized claw \n");
  } else return -1;
  sleep(1);
  claw_Throw();
  sleep(1);
  /*sleep(5);
  get_tacho_position(big_motor, &big_motor_pos);
  printf("Position: %d \n",big_motor_pos); */
  //sleep(5);
  claw_Lower();
  sleep(1);
  claw_Grab();
  bool hold = claw_HoldsBall();
  printf("Hold value is %d \n", hold);
  sleep(3);
  claw_Throw();
  
  
  return 0;
}

// initialization
int claw_Init()
{
  if ( ev3_init() == -1 ){
    printf("Could not initialize robot or claw\n");
    return 1;
  }
  
  while ( ev3_tacho_init() < 1 ){
    sleep( 10 );
    printf("looking for taco\n");
  }
  
  // init of small motor
  if (ev3_search_tacho_plugged_in(port_small_motor, 0, &small_motor, 0 )){
    printf("found motor connected to port: %d\n", port_small_motor);
    get_tacho_max_speed       ( small_motor, &max_speed_small_motor   );
    set_tacho_speed_sp        ( small_motor, max_speed_small_motor/10 );
    set_tacho_stop_action_inx ( small_motor, TACHO_COAST              );
    set_tacho_position_sp     ( small_motor, -50                      );
    set_tacho_command_inx     ( small_motor, TACHO_RUN_TO_REL_POS     );
    
    do {
      get_tacho_state_flags   ( small_motor, &state_small_motor       );
    } while ( state_small_motor == TACHO_RUNNING || state_small_motor == TACHO_RAMPING );
    
    printf( "Calibrating shooter in default position \n" );
    set_tacho_command_inx     (small_motor, TACHO_RESET               );
    do {
      get_tacho_state_flags   ( small_motor, &state_small_motor       );
      printf("state of small motor: %d \n", state_small_motor);
    } while ( state_small_motor != 0 );
    printf("Position: %d \n",small_motor_pos);
    
    
  }
  
  
  // init of big motor
  if ( ev3_search_tacho_plugged_in( port_big_motor, 0, &big_motor, 0 )){
    printf("found motor connected to port: %d\n", port_big_motor);
    get_tacho_max_speed       ( big_motor, &max_speed_big_motor   );
    
    set_tacho_speed_sp        ( big_motor, max_speed_big_motor/10 );
    set_tacho_stop_action_inx ( big_motor, TACHO_COAST            );
    set_tacho_position_sp     ( big_motor, -100                   );
    set_tacho_command_inx     ( big_motor, TACHO_RUN_TO_REL_POS   );
    
    do {
      get_tacho_state_flags   ( big_motor, &state_big_motor       );
    } while ( state_big_motor == TACHO_RUNNING || state_big_motor == TACHO_RAMPING );
    
    printf( "Calibrating claw in default position \n" );
    set_tacho_command_inx     (big_motor, TACHO_RESET             );
    do {
      get_tacho_state_flags   ( big_motor, &state_big_motor       );
    } while ( state_big_motor != 0);
    printf("Position: %d \n",big_motor_pos);
    
    
  }
  printf( "Tacho is now ready \n" );
  return 0;
}

int claw_Lower()
{
  set_tacho_speed_sp  ( big_motor, max_speed_big_motor/15     );
  set_tacho_speed_sp  ( small_motor, max_speed_small_motor/10 );
  
  /*
  set_tacho_stop_action_inx ( small_motor, TACHO_COAST          );
  set_tacho_position_sp     ( small_motor, 0                    );
  set_tacho_command_inx     ( small_motor, TACHO_RUN_TO_ABS_POS );
  
  do {
    get_tacho_state_flags   ( small_motor, &state_small_motor   );
  } while ( state_small_motor != 0 );
  */
   
  set_tacho_stop_action_inx ( big_motor, TACHO_COAST            );
  set_tacho_position_sp     ( big_motor, 100                    );
  set_tacho_command_inx     ( big_motor, TACHO_RUN_TO_ABS_POS   );
  
  do {
    get_tacho_state_flags   ( big_motor, &state_big_motor       );
  } while ( state_big_motor != 0 );

  return 0;
}




int claw_Grab()
{
  set_tacho_speed_sp        ( big_motor, max_speed_big_motor/10     );
  set_tacho_speed_sp        ( small_motor, max_speed_small_motor/10 );
  
  set_tacho_stop_action_inx ( small_motor, TACHO_HOLD               );
  set_tacho_position_sp     ( small_motor, -100                     );
  
  set_tacho_command_inx     ( small_motor, TACHO_RUN_TO_REL_POS     );
  do {
    get_tacho_state_flags   ( small_motor, &state_small_motor       );
    //printf("Tacho state during grab: %d \n", state_small_motor);
  } while ( state_small_motor == TACHO_RUNNING || state_small_motor == TACHO_RAMPING );
  
  set_tacho_stop_action_inx (big_motor, TACHO_COAST                 );
  set_tacho_position_sp     (big_motor, 0                           );
  set_tacho_command_inx     (big_motor, TACHO_RUN_TO_ABS_POS        );
  
  return 0;
}

bool claw_HoldsBall()
{
  get_tacho_state_flags (small_motor, &state_small_motor);
  
  if (state_small_motor == 9) return true;
  else return false;
}

int claw_Throw()
{
  set_tacho_speed_sp        ( small_motor, max_speed_small_motor  );
  
  set_tacho_stop_action_inx ( small_motor, TACHO_COAST            );
  set_tacho_position_sp     ( small_motor, 400                    );
  set_tacho_command_inx     ( small_motor, TACHO_RUN_TO_REL_POS   );
  
  do {
    get_tacho_state_flags   ( small_motor, &state_small_motor     );
  } while ( state_small_motor != 0 );
  
  
  return 0;
}
