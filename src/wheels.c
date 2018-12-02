
#include <stdio.h>
#include <stdlib.h>
#include "ev3/ev3.h"
#include "ev3/ev3_port.h"
#include "ev3/ev3_tacho.h"


#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 );

int initTachos();
int turnDegRight(int deg);
int turnRight();
int turnLeft();

uint8_t rsn;
uint8_t lsn;
int right_port = 66;
int left_port = 67;
int max_speed;

int main(){

  //initializing motors
  initTachos();
  //setting the max_speed variable
  get_tacho_max_speed( rsn, &max_speed );
  //running funcitons
  turnDegRight(180);
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
    printf("found motor connected to port: %d\n", right_port);
  }
  if (ev3ev3_search_tacho_plugged_in(left_port, 0, &lsn, 0 )){
    printf("found motor connected to port: %d\n",left_port);
  }

  printf( "Tacho is now awake and ready \n" );
  return 0;
}


int turnDegRight(int deg){
  printf( "run to relative position...\n" );
  set_tacho_speed_sp( rsn, max_speed / 2 );
  set_tacho_ramp_up_sp( rsn, 0 );
  set_tacho_ramp_down_sp( rsn, 0 );
  set_tacho_position_sp( rsn, deg );
  set_tacho_stop_action(rsn, TACHO_BRAKE);

  set_tacho_speed_sp( lsn, max_speed / 2 );
  set_tacho_ramp_up_sp( lsn, 0 );
  set_tacho_ramp_down_sp( lsn, 0 );
  set_tacho_position_sp( lsn, -deg );
  set_tacho_stop_action(lsn, TACHO_BRAKE);

  set_tacho_command_inx( rsn, TACHO_RUN_TO_REL_POS );
  set_tacho_command_inx( lsn, TACHO_RUN_TO_REL_POS );

  return 0;
}
/*
int turnLeft(){
  set_tacho_speed_sp( rsn, max_speed * 2 / 3 );
  set_tacho_speed_sp( lsn, -max_speed * 2 / 3 );

  set_tacho_time_sp( lsn, 50 );
  set_tacho_ramp_up_sp( lsn, 10 );
  set_tacho_ramp_down_sp( lsn, 10 );
  set_tacho_time_sp( rsn, 50 );
  set_tacho_ramp_up_sp( rsn, 20 );
  set_tacho_ramp_down_sp( rsn, 20 );

  set_tacho_command_inx( rsn, TACHO_RUN_TIMED );
  set_tacho_command_inx( lsn, TACHO_RUN_TIMED );

  return 0;
}                                                                                                                                       33,0-1        Bot
*/
