#include <stdio.h>
#include <stdlib.h>
#include "lib/ev3.h"
#include "lib/ev3_port.h"
#include "lib/ev3_tacho.h"
#include <unistd.h>
#include "lib/ev3_sensor.h"
#include "claw.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )

uint8_t sn_big;
uint8_t sn_small;

uint8_t big_motor;
int port_big_motor = 66;
int relative_position_big_motor;
int max_speed_big_motor;

uint8_t small_motor;
static int port_small_motor = 65;
int relative_position_small_motor;
int max_speed_small_motor; // Might not be neccesary

int claw_Init();
int claw_Lower();
int claw_Grab();
int claw_Throw();

int main(){
  if(claw_Init() == 0)
  {
    printf("Initialized claw \n");
  } else return -1;
  sleep(3);
  claw_Lower();
  sleep(2);
  claw_Grab();
  sleep(2);
  //set_tacho_command_inx(small_motor, TACHO_STOP);
  claw_Throw();
  
  
  return 0;
}

int claw_Init()
{
  if ( ev3_init() == -1 ){
    printf("Could not initialize robot or claw\n");
    return 1;
  }
  while ( ev3_tacho_init() < 1 ){
    Sleep( 1000 );
    printf("looking for taco\n");
  }
  // init of big motor in the bottom of claw
  if (ev3_search_tacho_plugged_in( port_big_motor, 0 , &big_motor, 0 )){
    printf("found motor connected to port: %d\n", port_big_motor);
    //set_tacho_command_inx(big_motor, TACHO_RESET);
    get_tacho_max_speed( big_motor, &max_speed_big_motor );
    
    set_tacho_speed_sp( big_motor, max_speed_big_motor / 10 );
    set_tacho_stop_action_inx(big_motor, TACHO_COAST);
    set_tacho_position_sp( big_motor, -50 );
    printf( "Set claw to default position \n" );
    set_tacho_command_inx(big_motor, TACHO_RUN_TO_ABS_POS);
    
    //set_tacho_ramp_up_sp( big_motor, max_speed_big_motor / 10 );
    //set_tacho_ramp_down_sp( big_motor, max_speed_big_motor / 10 );
  }
  // init of small motor at the top of claw. 
  if (ev3_search_tacho_plugged_in(port_small_motor, 0, &small_motor, 0 )){
    printf("found motor connected to port: %d\n", port_small_motor);
    set_tacho_command_inx(small_motor, TACHO_RESET);
    get_tacho_max_speed( small_motor, &max_speed_small_motor );
    
    set_tacho_speed_sp( small_motor, max_speed_small_motor / 10 );
    set_tacho_stop_action_inx(small_motor, TACHO_COAST);
    set_tacho_position_sp( small_motor, 70 );
    printf( "Set shooter to default position \n" );
    set_tacho_command_inx(small_motor, TACHO_RUN_TO_ABS_POS);
    //sleep(10);
    //set_tacho_command_inx(small_motor, TACHO_STOP);
    
    //set_tacho_ramp_up_sp( small_motor, max_speed_small_motor / 4 ); // Ramp up, og ramp down vil være forskjellig for grab og throw
    //set_tacho_ramp_down_sp( small_motor, max_speed_small_motor / 4 );
  }
  printf( "Tacho is now ready \n" );
  return 0;
}

// do {
//   get_tacho_state_flags( sn, &state );
// } while ( state );
// printf( "run to relative position...\n" );
// set_tacho_speed_sp( sn, max_speed / 2 );
// set_tacho_ramp_up_sp( sn, 0 );
// set_tacho_ramp_down_sp( sn, 0 );
// set_tacho_position_sp( sn, 90 );
// for ( i = 0; i < 8; i++ ) {
//   set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
//   Sleep( 500 );
// }

int claw_Lower()
{
  set_tacho_speed_sp( big_motor, max_speed_big_motor/10 );
  set_tacho_speed_sp( small_motor, max_speed_small_motor/10);
  
  printf( "Lower claw... \n" );
  set_tacho_stop_action_inx(small_motor, TACHO_COAST);
  set_tacho_position_sp(small_motor, 70);
  set_tacho_command_inx(small_motor, TACHO_RUN_TO_ABS_POS);
  sleep(1);
  set_tacho_stop_action_inx(big_motor, TACHO_COAST);
  set_tacho_position_sp( big_motor, 90);
  set_tacho_command_inx(big_motor, TACHO_RUN_TO_ABS_POS);
  printf( "Claw lowered... \n" );
  
  

  return 0;
}




int claw_Grab()
{
  set_tacho_speed_sp( big_motor, max_speed_big_motor/10 );
  set_tacho_speed_sp( small_motor, max_speed_small_motor/10);
  
  set_tacho_stop_action_inx(small_motor, TACHO_HOLD);
  set_tacho_position_sp(small_motor, -90);
  
  set_tacho_command_inx( small_motor, TACHO_RUN_TO_REL_POS );
  
  sleep(3);
  set_tacho_position_sp(big_motor, -50);
  set_tacho_command_inx(big_motor, TACHO_RUN_TO_ABS_POS);
  
  return 0;
}

int claw_Throw()
{
  set_tacho_speed_sp( small_motor, max_speed_small_motor);
  
  set_tacho_position_sp(small_motor, 400);
  set_tacho_command_inx(small_motor, TACHO_RUN_TO_REL_POS);

  sleep(3);
  set_tacho_stop_action_inx(small_motor, TACHO_COAST);
  set_tacho_position_sp(small_motor, 0);
  set_tacho_command_inx(small_motor, TACHO_RUN_TO_REL_POS);
  
  return 0;
}
