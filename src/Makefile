CC=arm-linux-gnueabi-gcc
CFLAGS=-Wall -std=c11

adapters: adapters/*.c
	$(CC) $(CFLAGS) adapters/*.c -c

test: test.c 
	$(CC) $(CFLAGS) test.c adapters/*.o obj/*.o -o test
