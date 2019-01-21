#ifndef BT_H
#define BT_H

// Protocol
#define BT_MSG_ACC              0
#define BT_MSG_START            1
#define BT_MSG_STOP             2
#define BT_MSG_KICK             3
#define BT_MSG_SCORE            4
#define BT_MSG_CUSTOM           8

#define BT_MAX_MSG_LENGTH       58

/**
 * Initializes the bluetooth module and sets the desired server address and
 * team id.
 * @param server_address The address of the server (a string)
 * @param team_id The id of the group (integer)
 * @returns int
 *      0 = success
 *      1 = failure
 */
int bt_Connect(const char *server_address, int team_id);

/**
 * Waits (blocks program execution) until the module receives a start message
 * from the server.
 * @returns int
 *      0 = success
 *      1 = something went wrong
 */
int bt_WaitForStartMessage();

/**
 * Sends a score message to the server, either for a short or a long shot.
 * @param long_shot Wether the shot was long or not
 * @returns int The number of bytes sent to the server or a negative number if
 * something went wrong
 */
int bt_SendScoreMessage(int long_shot);

/**
 * Disconnects from server
 * @returns int
 *      0 = success
 *      1 = failure
 */
int bt_Disconnect();

#endif
