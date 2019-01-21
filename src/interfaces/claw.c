#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "claw.h"

#include "utils.h"

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
int max_speed_small_motor;
FLAGS_T state_small_motor;

int big_motor_pos;
int small_motor_pos;

static const char *mn = "  CLAW  ";

// initialization
int claw_Init()
{
  if ( ev3_init() == -1 ){
    utils_Err(mn, "Could not initialize robot or claw");
    return 1;
  }
  
  while ( ev3_tacho_init() < 1 ){
    utils_Sleep(1000);
    utils_Log(mn, "Looking for tacos...");
    
  }
  
  // init of small motor
  if (ev3_search_tacho_plugged_in(port_small_motor, 0, &small_motor, 0 )){
    utils_Log(mn, "Small motor found"); 
    get_tacho_max_speed       ( small_motor, &max_speed_small_motor   );
    
    // moving motor to default position
    set_tacho_speed_sp        ( small_motor, max_speed_small_motor/10 );
    set_tacho_stop_action_inx ( small_motor, TACHO_COAST              );
    set_tacho_position_sp     ( small_motor, -50                      );
    set_tacho_command_inx     ( small_motor, TACHO_RUN_TO_REL_POS     );
    
    do {
      get_tacho_state_flags   ( small_motor, &state_small_motor       );
    } while ( state_small_motor == TACHO_RUNNING || state_small_motor == TACHO_RAMPING );
    
    // resetting motor when in default position
    set_tacho_command_inx     (small_motor, TACHO_RESET               );
    do {
      get_tacho_state_flags   ( small_motor, &state_small_motor       );
    } while ( state_small_motor != 0 );
    
  }
  else
  {
      utils_Err(mn, "Small motor not found");
      return 2;
  }
  
  
  
  // init of big motor
  if ( ev3_search_tacho_plugged_in( port_big_motor, 0, &big_motor, 0 )){
    utils_Log(mn, "Large motor found");

    get_tacho_max_speed       ( big_motor, &max_speed_big_motor   );
    
    // moving motor to default postion
    set_tacho_speed_sp        ( big_motor, max_speed_big_motor/10 );
    set_tacho_stop_action_inx ( big_motor, TACHO_COAST            );
    set_tacho_position_sp     ( big_motor, -100                   );
    set_tacho_command_inx     ( big_motor, TACHO_RUN_TO_REL_POS   );
    
    do {
      get_tacho_state_flags   ( big_motor, &state_big_motor       );
    } while ( state_big_motor == TACHO_RUNNING || state_big_motor == TACHO_RAMPING );
    
    // resetting motor when in default postion
    set_tacho_command_inx     (big_motor, TACHO_RESET             );
    do {
      get_tacho_state_flags   ( big_motor, &state_big_motor       );
    } while ( state_big_motor != 0);
    
  }
  else
  {
      utils_Err(mn, "Large motor not found");
      return 3;
  }
  utils_Log(mn, "Ready");
  return 0;
}

int claw_Lower()
{
  printf("[claw_Lower]: In function, before motor-com \n");
  set_tacho_speed_sp  ( big_motor, max_speed_big_motor/15       );
  set_tacho_stop_action_inx ( big_motor, TACHO_COAST            );
  set_tacho_position_sp     ( big_motor, 100                    );
  set_tacho_command_inx     ( big_motor, TACHO_RUN_TO_ABS_POS   );
  printf("[claw_Lower]: Com with motors finished \n");
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
  } while ( state_small_motor == TACHO_RUNNING || state_small_motor == TACHO_RAMPING );
  
  set_tacho_stop_action_inx (big_motor, TACHO_COAST                 );
  set_tacho_position_sp     (big_motor, 0                           );
  set_tacho_command_inx     (big_motor, TACHO_RUN_TO_ABS_POS        );
  
  do {
    get_tacho_state_flags   ( big_motor, &state_big_motor           );
  } while ( state_big_motor == TACHO_RUNNING || state_big_motor == TACHO_RAMPING );
  
  return 0;
}

int claw_HoldsBall()
{
  get_tacho_state_flags (small_motor, &state_small_motor);
  
  return ((state_small_motor & 0x10) == 0x10);
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
  
  //claw_Reset();
  return 0;
}

int claw_Drop()
{
  set_tacho_speed_sp        ( small_motor, max_speed_small_motor/20 );
  set_tacho_speed_sp        ( big_motor, max_speed_big_motor/20     );
  
  set_tacho_position_sp     ( small_motor, 90                       );
  set_tacho_position_sp     ( big_motor, 50                         );
  
  set_tacho_stop_action_inx ( small_motor, TACHO_COAST              );
  set_tacho_stop_action_inx ( big_motor, TACHO_HOLD                 );
  
  set_tacho_command_inx     ( big_motor, TACHO_RUN_TO_ABS_POS       );
  
  do {
    get_tacho_state_flags   ( big_motor, &state_big_motor           );
  } while ( state_big_motor == TACHO_RUNNING || state_big_motor == TACHO_RAMPING );
    
    set_tacho_command_inx   ( small_motor, TACHO_RUN_TO_REL_POS     );
  
  do {
    get_tacho_state_flags   ( small_motor, &state_small_motor       );
  } while ( state_small_motor != 0 );
  
  return 0;
}

int claw_TakeBall()
{
  claw_Lower();

  utils_Sleep(500);
  claw_Grab();
  int holds = claw_HoldsBall();
  if (!holds) 
  {
      utils_Log(mn, "Failed to take ball");
  }
  return holds;
}

int claw_Reset()
{
  set_tacho_speed_sp        ( big_motor, max_speed_big_motor/10 );
  set_tacho_stop_action_inx ( big_motor, TACHO_COAST            );
  set_tacho_position_sp     ( big_motor, 0                      );
  set_tacho_command_inx     ( big_motor, TACHO_RUN_TO_ABS_POS   );
  
  set_tacho_speed_sp        ( small_motor, max_speed_small_motor/10 );
  set_tacho_stop_action_inx ( small_motor, TACHO_COAST              );
  set_tacho_position_sp     ( small_motor, 0                        );
  set_tacho_command_inx     ( small_motor, TACHO_RUN_TO_ABS_POS     );
  
  do {
    get_tacho_state_flags   ( small_motor, &state_small_motor       );
    get_tacho_state_flags   ( big_motor, &state_big_motor           );
  } while ( state_small_motor != 0 && state_big_motor != 0);
  return 0;
}
