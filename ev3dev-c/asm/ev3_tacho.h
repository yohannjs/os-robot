
/*  ev3_tacho.h was generated by yup.py (yupp) 1.0c6
    out of ev3_tacho.yu-h 
 *//**
 *  \file  ev3_tacho.h (ev3_tacho.yu-h)
 *  \brief  EV3 Tacho Motors.
 *  \author  Vitaly Kravtsov (in4lio@gmail.com)
 *  \copyright  See the LICENSE file.
 */

#pragma once

#include "enum-asm.h"

#define TACHO_DIR  "/sys/class/tacho-motor"  /**< Directory of tachos. */

#define TACHO_DESC__LIMIT_  DESC_LIMIT  /**< Limit of tacho descriptors. */

#define TACHO__NONE_  TACHO_DESC__LIMIT_  /**< Tacho is not found. */

/**
 *  \var EV3_TACHO ev3_tacho[ TACHO_DESC__LIMIT_ ]
 *  \brief Vector of tacho descriptors (filled by \ref ev3_tacho_init).
 */
.extern ev3_tacho

/**
 *  \brief Identifiers of tacho types.
 */
ENUM_0  TACHO_TYPE__NONE_  /* XXX: memset( 0 ) is used */
ENUM_N  LEGO_EV3_L_MOTOR
ENUM_N  LEGO_EV3_M_MOTOR
ENUM_N  FI_L12_EV3

ENUM_N  TACHO_TYPE__COUNT_  /**< Count of tacho types. */
ENUM_EQ TACHO_TYPE__UNKNOWN_, TACHO_TYPE__COUNT_

/**
 *  \brief Common identifiers of tacho "command" attribute.
 */
ENUM_0  TACHO_COMMAND__NONE_

ENUM_N  TACHO_RUN_FOREVER
ENUM_N  TACHO_RUN_TO_ABS_POS
ENUM_N  TACHO_RUN_TO_REL_POS
ENUM_N  TACHO_RUN_TIMED
ENUM_N  TACHO_RUN_DIRECT
ENUM_N  TACHO_STOP
ENUM_N  TACHO_RESET

ENUM_N  TACHO_COMMAND__COUNT_  /**< Count of tacho "command" attribute. */
ENUM_EQ TACHO_COMMAND__UNKNOWN_, TACHO_COMMAND__COUNT_

/**
 *  \brief Common identifiers of tacho "polarity" attribute.
 */
ENUM_0  TACHO_POLARITY__NONE_

ENUM_N  TACHO_NORMAL
ENUM_N  TACHO_INVERSED

ENUM_N  TACHO_POLARITY__COUNT_  /**< Count of tacho "polarity" attribute. */
ENUM_EQ TACHO_POLARITY__UNKNOWN_, TACHO_POLARITY__COUNT_

/**
 *  \brief Common identifiers of tacho "stop_action" attribute.
 */
ENUM_0  TACHO_STOP_ACTION__NONE_

ENUM_N  TACHO_COAST
ENUM_N  TACHO_BRAKE
ENUM_N  TACHO_HOLD

ENUM_N  TACHO_STOP_ACTION__COUNT_  /**< Count of tacho "stop_action" attribute. */
ENUM_EQ TACHO_STOP_ACTION__UNKNOWN_, TACHO_STOP_ACTION__COUNT_

/**
 *  \brief Common identifiers of tacho "state" attribute.
 */
ENUM_0  TACHO_STATE__NONE_

ENUM_EQ TACHO_RUNNING, 0x1
ENUM_EQ TACHO_RAMPING, 0x2
ENUM_EQ TACHO_HOLDING, 0x4
ENUM_EQ TACHO_OVERLOADED, 0x8
ENUM_EQ TACHO_STALLED, 0x10

/**
 *  \fn size_t get_tacho_address( uint8_t sn, char *buf, size_t sz )
 *  \brief Read "address" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
.extern get_tacho_address

/**
 *  \fn size_t set_tacho_command( uint8_t sn, char *value )
 *  \brief Write "command" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_command

/**
 *  \fn size_t multi_set_tacho_command( uint8_t *sn, char *value )
 *  \brief Write "command" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_command

/**
 *  \fn size_t get_tacho_commands( uint8_t sn, char *buf, size_t sz )
 *  \brief Read "commands" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
.extern get_tacho_commands

/**
 *  \fn size_t get_tacho_count_per_rot( uint8_t sn, int *buf )
 *  \brief Read "count_per_rot" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_count_per_rot

/**
 *  \fn size_t get_tacho_count_per_m( uint8_t sn, int *buf )
 *  \brief Read "count_per_m" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_count_per_m

/**
 *  \fn size_t get_tacho_full_travel_count( uint8_t sn, int *buf )
 *  \brief Read "full_travel_count" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_full_travel_count

/**
 *  \fn size_t get_tacho_driver_name( uint8_t sn, char *buf, size_t sz )
 *  \brief Read "driver_name" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
.extern get_tacho_driver_name

/**
 *  \fn size_t get_tacho_duty_cycle( uint8_t sn, int *buf )
 *  \brief Read "duty_cycle" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_duty_cycle

/**
 *  \fn size_t get_tacho_duty_cycle_sp( uint8_t sn, int *buf )
 *  \brief Read "duty_cycle_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_duty_cycle_sp

/**
 *  \fn size_t set_tacho_duty_cycle_sp( uint8_t sn, int value )
 *  \brief Write "duty_cycle_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_duty_cycle_sp

/**
 *  \fn size_t multi_set_tacho_duty_cycle_sp( uint8_t *sn, int value )
 *  \brief Write "duty_cycle_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_duty_cycle_sp

/**
 *  \fn size_t get_tacho_hold_pid_Kd( uint8_t sn, int *buf )
 *  \brief Read "hold_pid/Kd" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_hold_pid_Kd

/**
 *  \fn size_t set_tacho_hold_pid_Kd( uint8_t sn, int value )
 *  \brief Write "hold_pid/Kd" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_hold_pid_Kd

/**
 *  \fn size_t multi_set_tacho_hold_pid_Kd( uint8_t *sn, int value )
 *  \brief Write "hold_pid/Kd" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_hold_pid_Kd

/**
 *  \fn size_t get_tacho_hold_pid_Ki( uint8_t sn, int *buf )
 *  \brief Read "hold_pid/Ki" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_hold_pid_Ki

/**
 *  \fn size_t set_tacho_hold_pid_Ki( uint8_t sn, int value )
 *  \brief Write "hold_pid/Ki" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_hold_pid_Ki

/**
 *  \fn size_t multi_set_tacho_hold_pid_Ki( uint8_t *sn, int value )
 *  \brief Write "hold_pid/Ki" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_hold_pid_Ki

/**
 *  \fn size_t get_tacho_hold_pid_Kp( uint8_t sn, int *buf )
 *  \brief Read "hold_pid/Kp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_hold_pid_Kp

/**
 *  \fn size_t set_tacho_hold_pid_Kp( uint8_t sn, int value )
 *  \brief Write "hold_pid/Kp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_hold_pid_Kp

/**
 *  \fn size_t multi_set_tacho_hold_pid_Kp( uint8_t *sn, int value )
 *  \brief Write "hold_pid/Kp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_hold_pid_Kp

/**
 *  \fn size_t get_tacho_max_speed( uint8_t sn, int *buf )
 *  \brief Read "max_speed" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_max_speed

/**
 *  \fn size_t get_tacho_polarity( uint8_t sn, char *buf, size_t sz )
 *  \brief Read "polarity" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
.extern get_tacho_polarity

/**
 *  \fn size_t set_tacho_polarity( uint8_t sn, char *value )
 *  \brief Write "polarity" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_polarity

/**
 *  \fn size_t multi_set_tacho_polarity( uint8_t *sn, char *value )
 *  \brief Write "polarity" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_polarity

/**
 *  \fn size_t get_tacho_position( uint8_t sn, int *buf )
 *  \brief Read "position" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_position

/**
 *  \fn size_t set_tacho_position( uint8_t sn, int value )
 *  \brief Write "position" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_position

/**
 *  \fn size_t multi_set_tacho_position( uint8_t *sn, int value )
 *  \brief Write "position" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_position

/**
 *  \fn size_t get_tacho_position_sp( uint8_t sn, int *buf )
 *  \brief Read "position_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_position_sp

/**
 *  \fn size_t set_tacho_position_sp( uint8_t sn, int value )
 *  \brief Write "position_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_position_sp

/**
 *  \fn size_t multi_set_tacho_position_sp( uint8_t *sn, int value )
 *  \brief Write "position_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_position_sp

/**
 *  \fn size_t get_tacho_ramp_down_sp( uint8_t sn, int *buf )
 *  \brief Read "ramp_down_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_ramp_down_sp

/**
 *  \fn size_t set_tacho_ramp_down_sp( uint8_t sn, int value )
 *  \brief Write "ramp_down_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_ramp_down_sp

/**
 *  \fn size_t multi_set_tacho_ramp_down_sp( uint8_t *sn, int value )
 *  \brief Write "ramp_down_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_ramp_down_sp

/**
 *  \fn size_t get_tacho_ramp_up_sp( uint8_t sn, int *buf )
 *  \brief Read "ramp_up_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_ramp_up_sp

/**
 *  \fn size_t set_tacho_ramp_up_sp( uint8_t sn, int value )
 *  \brief Write "ramp_up_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_ramp_up_sp

/**
 *  \fn size_t multi_set_tacho_ramp_up_sp( uint8_t *sn, int value )
 *  \brief Write "ramp_up_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_ramp_up_sp

/**
 *  \fn size_t get_tacho_speed( uint8_t sn, int *buf )
 *  \brief Read "speed" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_speed

/**
 *  \fn size_t get_tacho_speed_pid_Kd( uint8_t sn, int *buf )
 *  \brief Read "speed_pid/Kd" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_speed_pid_Kd

/**
 *  \fn size_t set_tacho_speed_pid_Kd( uint8_t sn, int value )
 *  \brief Write "speed_pid/Kd" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_speed_pid_Kd

/**
 *  \fn size_t multi_set_tacho_speed_pid_Kd( uint8_t *sn, int value )
 *  \brief Write "speed_pid/Kd" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_speed_pid_Kd

/**
 *  \fn size_t get_tacho_speed_pid_Ki( uint8_t sn, int *buf )
 *  \brief Read "speed_pid/Ki" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_speed_pid_Ki

/**
 *  \fn size_t set_tacho_speed_pid_Ki( uint8_t sn, int value )
 *  \brief Write "speed_pid/Ki" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_speed_pid_Ki

/**
 *  \fn size_t multi_set_tacho_speed_pid_Ki( uint8_t *sn, int value )
 *  \brief Write "speed_pid/Ki" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_speed_pid_Ki

/**
 *  \fn size_t get_tacho_speed_pid_Kp( uint8_t sn, int *buf )
 *  \brief Read "speed_pid/Kp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_speed_pid_Kp

/**
 *  \fn size_t set_tacho_speed_pid_Kp( uint8_t sn, int value )
 *  \brief Write "speed_pid/Kp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_speed_pid_Kp

/**
 *  \fn size_t multi_set_tacho_speed_pid_Kp( uint8_t *sn, int value )
 *  \brief Write "speed_pid/Kp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_speed_pid_Kp

/**
 *  \fn size_t get_tacho_speed_sp( uint8_t sn, int *buf )
 *  \brief Read "speed_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_speed_sp

/**
 *  \fn size_t set_tacho_speed_sp( uint8_t sn, int value )
 *  \brief Write "speed_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_speed_sp

/**
 *  \fn size_t multi_set_tacho_speed_sp( uint8_t *sn, int value )
 *  \brief Write "speed_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_speed_sp

/**
 *  \fn size_t get_tacho_state( uint8_t sn, char *buf, size_t sz )
 *  \brief Read "state" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
.extern get_tacho_state

/**
 *  \fn size_t get_tacho_stop_action( uint8_t sn, char *buf, size_t sz )
 *  \brief Read "stop_action" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
.extern get_tacho_stop_action

/**
 *  \fn size_t set_tacho_stop_action( uint8_t sn, char *value )
 *  \brief Write "stop_action" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_stop_action

/**
 *  \fn size_t multi_set_tacho_stop_action( uint8_t *sn, char *value )
 *  \brief Write "stop_action" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_stop_action

/**
 *  \fn size_t get_tacho_stop_actions( uint8_t sn, char *buf, size_t sz )
 *  \brief Read "stop_actions" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \param sz Buffer size.
 *  \return Count of read bytes.
 */
.extern get_tacho_stop_actions

/**
 *  \fn size_t get_tacho_time_sp( uint8_t sn, int *buf )
 *  \brief Read "time_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
		 
 *  \return Count of read bytes.
 */
.extern get_tacho_time_sp

/**
 *  \fn size_t set_tacho_time_sp( uint8_t sn, int value )
 *  \brief Write "time_sp" attribute of the tacho.
 *  \param sn Sequence number.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern set_tacho_time_sp

/**
 *  \fn size_t multi_set_tacho_time_sp( uint8_t *sn, int value )
 *  \brief Write "time_sp" attribute of several tachos.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param value Attribute value.
		 
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_time_sp

/**
 *  \fn const char *ev3_tacho_type( INX_T type_inx )
 *  \brief Get name of the specified tacho type.
 *  \param type_inx Index of the tacho type.
 *  \return Requested value.
 */
.extern ev3_tacho_type

/**
 *  \fn INX_T get_tacho_type_inx( uint8_t sn )
 *  \brief Read "driver_name" attribute and get index of the tacho type.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
.extern get_tacho_type_inx

/**
 *  \fn size_t get_tacho_desc( uint8_t sn, EV3_TACHO *desc )
 *  \brief Read tacho attributes that are required for filling the descriptor.
 *  \param sn Sequence number.
 *  \param desc Buffer for the descriptor.
 *  \return Count of read bytes.
 */
.extern get_tacho_desc

/**
 *  \fn EV3_TACHO *ev3_tacho_desc( uint8_t sn )
 *  \brief Get descriptor of the tacho.
 *  \param sn Sequence number.
 *  \return Pointer to the tacho descriptor.
 */
.extern ev3_tacho_desc

/**
 *  \fn INX_T ev3_tacho_desc_type_inx( uint8_t sn )
 *  \brief Get type from the tacho descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
.extern ev3_tacho_desc_type_inx

/**
 *  \fn uint8_t ev3_tacho_desc_port( uint8_t sn )
 *  \brief Get EV3 port from the tacho descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
.extern ev3_tacho_desc_port

/**
 *  \fn uint8_t ev3_tacho_desc_extport( uint8_t sn )
 *  \brief Get extended port from the tacho descriptor.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
.extern ev3_tacho_desc_extport

/**
 *  \fn char *ev3_tacho_port_name( uint8_t sn, char *buf )
 *  \brief Assemble EV3 port name from the tacho descriptor.
 *  \param sn Sequence number.
 *  \param[out] buf Buffer for result.
 *  \return Requested value.
 */
.extern ev3_tacho_port_name

/**
 *  \fn bool ev3_search_tacho( INX_T type_inx, uint8_t *sn, uint8_t from )
 *  \brief Search of a sequence number of the specified tacho type.
 *  \param type_inx Tacho type.
 *  \param[out] sn Buffer for the sequence number.
 *  \param from Search initial value.
 *  \return Flag - the tacho is found.
 */
.extern ev3_search_tacho

/**
 *  \fn bool ev3_search_tacho_plugged_in( uint8_t port, uint8_t extport, uint8_t *sn, uint8_t from )
 *  \brief Search of a sequence number the tacho by plug-in attributes.
 *  \param port EV3 port.
 *  \param extport Extended port.
 *  \param[out] sn Buffer for the sequence number.
 *  \param from Search initial value.
 *  \return Flag - the tacho is found.
 */
.extern ev3_search_tacho_plugged_in

/**
 *  \fn const char *ev3_tacho_command( INX_T command_inx )
 *  \brief Get name of the specified tacho command.
 *  \param command_inx Index of the tacho command.
 *  \return Requested value.
 */
.extern ev3_tacho_command

/**
 *  \fn size_t set_tacho_command_inx( uint8_t sn, INX_T command_inx )
 *  \brief Write "command" attribute of the tacho by the index.
 *  \param sn Sequence number.
 *  \param command_inx Index of the tacho command.
 *  \return Count of written bytes.
 */
.extern set_tacho_command_inx

/**
 *  \fn size_t multi_set_tacho_command_inx( uint8_t *sn, INX_T command_inx )
 *  \brief Write "command" attribute of several tachos by the index.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param command_inx Index of the tacho command.
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_command_inx

/**
 *  \fn const char *ev3_tacho_polarity( INX_T polarity_inx )
 *  \brief Get name of the specified tacho polarity.
 *  \param polarity_inx Index of the tacho polarity.
 *  \return Requested value.
 */
.extern ev3_tacho_polarity

/**
 *  \fn INX_T get_tacho_polarity_inx( uint8_t sn )
 *  \brief Read "polarity" attribute of the tacho and get the index.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
.extern get_tacho_polarity_inx

/**
 *  \fn size_t set_tacho_polarity_inx( uint8_t sn, INX_T polarity_inx )
 *  \brief Write "polarity" attribute of the tacho by the index.
 *  \param sn Sequence number.
 *  \param polarity_inx Index of the tacho polarity.
 *  \return Count of written bytes.
 */
.extern set_tacho_polarity_inx

/**
 *  \fn size_t multi_set_tacho_polarity_inx( uint8_t *sn, INX_T polarity_inx )
 *  \brief Write "polarity" attribute of several tachos by the index.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param polarity_inx Index of the tacho polarity.
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_polarity_inx

/**
 *  \fn const char *ev3_tacho_stop_action( INX_T stop_action_inx )
 *  \brief Get name of the specified tacho stop_action.
 *  \param stop_action_inx Index of the tacho stop_action.
 *  \return Requested value.
 */
.extern ev3_tacho_stop_action

/**
 *  \fn INX_T get_tacho_stop_action_inx( uint8_t sn )
 *  \brief Read "stop_action" attribute of the tacho and get the index.
 *  \param sn Sequence number.
 *  \return Requested value.
 */
.extern get_tacho_stop_action_inx

/**
 *  \fn size_t set_tacho_stop_action_inx( uint8_t sn, INX_T stop_action_inx )
 *  \brief Write "stop_action" attribute of the tacho by the index.
 *  \param sn Sequence number.
 *  \param stop_action_inx Index of the tacho stop_action.
 *  \return Count of written bytes.
 */
.extern set_tacho_stop_action_inx

/**
 *  \fn size_t multi_set_tacho_stop_action_inx( uint8_t *sn, INX_T stop_action_inx )
 *  \brief Write "stop_action" attribute of several tachos by the index.
 *  \param sn Vector of sequence numbers ending with DESC_LIMIT.
 *  \param stop_action_inx Index of the tacho stop_action.
 *  \return Count of written bytes.
 */
.extern multi_set_tacho_stop_action_inx

/**
 *  \fn size_t get_tacho_state_flags( uint8_t sn, FLAGS_T *flags )
 *  \brief Read "state" attribute of the tacho and get the flags.
 *  \param sn Sequence number.
 *  \param flags Buffer for the flags.
 *  \return Count of read bytes.
 */
.extern get_tacho_state_flags

/**
 *  \fn int ev3_tacho_init( void )
 *  \brief Detect connected tachos.
 *  \return Number of found tachos or -1 in case of an error.
 */
.extern ev3_tacho_init

