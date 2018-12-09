#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#define Sleep( msec ) usleep(( msec ) * 1000 )

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

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
    if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
      printf( "COLOR sensor is found, reading COLOR...\n" );
      if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
        val = 0;
      }
      printf( "\r(%s) \n", color[ val ]);
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
