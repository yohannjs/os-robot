#include <stdio.h>
#include <stdlib.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include <unistd.h>
#include "ev3_sensor.h"
#include "claw.h"

uint8_t sn_big;
uint8_t sn_small;

uint8_t big_motor;
int big_motor_port = 66;
int relative_position_big_motor;
uint8_t small_motor;
int small_motor_port = 67;
int max_speed; // Might not be neccesary
// get_tacho_max_speed( sn, &max_speed )
int initTachos();

int main(){

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
  if (ev3_search_tacho_plugged_in( big_motor_port,0 , &big_motor, 0 )){
    set_tacho_stop_action_inx(big_motor, TACHO_HOLD);
    set_tacho_ramp_up_sp( big_motor, 5 );
    set_tacho_ramp_down_sp( big_motor, 5 );
    printf("found motor connected to port: %d\n", big_motor_port);
  }
  if (ev3_search_tacho_plugged_in(small_motor_port, 0, &small_motor, 0 )){
    set_tacho_stop_action_inx(small_motor, TACHO_HOLD);
    set_tacho_ramp_up_sp( small_motor, 5 );
    set_tacho_ramp_down_sp( small_motor, 5 );
    printf("found motor connected to port: %d\n",small_motor_port);
  }
  printf( "Tacho is now ready \n" );
  return 0;
}