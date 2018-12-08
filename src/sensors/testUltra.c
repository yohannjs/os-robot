#include <stdio.h>
#include <stdlib.h>
#include <ev3.h>
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

static bool _check_pressed( uint8_t sn )
{
  int val;
    
  if ( sn == SENSOR__NONE_ ) {
    return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
    }
    return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}




int main( void )
{
  int i;
  uint8_t sn;
  FLAGS_T state;
  uint8_t sn_touch;
  uint8_t sn_color;
  uint8_t sn_compass;
  uint8_t sn_sonar;
  uint8_t sn_mag;
  char s[ 256 ];
  int val;
  float value;
  uint32_t n, ii;
  
  ev3_sensor_init();
  
  if ( ev3_init() == -1 ) return ( 1 );
  
  for ( i = 0; i < DESC_LIMIT; i++ ) {
    if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
      printf( "  type = %s\n", ev3_sensor_type( ev3_sensor[ i ].type_inx ));
      printf( "  port = %s\n", ev3_sensor_port_name( i, s ));
      if ( get_sensor_mode( i, s, sizeof( s ))) {
        printf( "  mode = %s\n", s );
      }
      if ( get_sensor_num_values( i, &n )) {
        for ( ii = 0; ii < n; ii++ ) {
          if ( get_sensor_value( ii, i, &val )) {
            printf( "  value%d = %d\n", ii, val );
          }
        }
      }
    }
  }
  
  if ( ev3_search_sensor( LEGO_EV3_TOUCH, &sn_touch, 0 )) {
    printf( "TOUCH sensor is found, press BUTTON for EXIT...\n" );
  }
    
  for ( ; ; ){
    if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
      printf("SONAR found, reading sonar...\n");
      if ( !get_sensor_value0(sn_sonar, &value )) {
        value = 0;
      }
      printf( "\r(%f) \n", value);
      fflush( stdout );
    }
    if ( _check_pressed( sn_touch )) break;
    Sleep( 200 );
    printf( "\r        " );
    fflush( stdout );
    if ( _check_pressed( sn_touch )) break;
    Sleep( 200 );
  }
  
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return ( 0 );
}
