#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define SERV_ADDR   "38:ba:f8:5a:6b:9d"     /* Whatever the address of the server is */
#define TEAM_ID     5                       /* Your team ID */

#define MSG_ACK         0
#define MSG_START       1
#define MSG_STOP        2
#define MSG_KICK        3
#define MSG_SCORE       4
#define MSG_CUSTOM 	8

#define Sleep( msec ) usleep(( msec ) * 1000 )

int s;

uint16_t msgId = 0;

int read_from_server (int sock, char *buffer, size_t maxSize) {
  int bytes_read = read (sock, buffer, maxSize);

  if (bytes_read <= 0) {
    fprintf (stderr, "Server unexpectedly closed connection...\n");
    close (s);
    exit (EXIT_FAILURE);
  }

  printf ("[DEBUG] received %d bytes\n", bytes_read);

  return bytes_read;
}

void robot () {
  char string[58];
  char type;

  srand(time(NULL));
  /* Send 3 SCORE messages */
  int i;
  for (i=0; i<3; i++){
    *((uint16_t *) string) = msgId++;
    string[2] = 1;
    string[3] = 0xFF;
    string[4] = MSG_SCORE;
    string[5] = 1; 
    printf("I wrote %d bytes to the server\n", write(s, string, 6));
    Sleep( 1000 );
  }
  printf("I'm waiting for the stop message\n");
  
  while(1) {
    //Wait for stop message
    read_from_server (s, string, 58);
    type = string[4];
    if (type ==MSG_STOP){
      return;
    }
  }
}


int main(int argc, char **argv) {
  struct sockaddr_rc addr = { 0 };
  int status;

  /* allocate a socket */
  s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

  /* set the connection parameters (who to connect to) */
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba (SERV_ADDR, &addr.rc_bdaddr);

  /* connect to server */
  status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

  /* if connected */
  if( status == 0 ) {
    printf("Connected to server\n");
    char string[58];

    /* Wait for START message */
    printf("Waiting for start message...\n");
    read_from_server (s, string, 9);
    if (string[4] == MSG_START) {
      printf ("Received start message!\n");
    }

    robot();

  } else {
    fprintf (stderr, "Failed to connect to server...\n");
    sleep (2);
    exit (EXIT_FAILURE);
  }

  close(s);
  return 0;
}
