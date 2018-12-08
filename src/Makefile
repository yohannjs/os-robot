CC=arm-linux-gnueabi-gcc
CFLAGS=-Wall -std=c11

ev3: lib/*.c
	$(CC) lib/*.c -c 

main: main.c 
	$(CC) $(CFLAGS) main.c ev3.o ev3_port.o ev3_tacho.o ev3_sensor.o -o main
