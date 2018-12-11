CC = arm-linux-gnueabi-gcc -Wall -std=c11

adapters: adapters/*.c
	$(CC) $(CFLAGS) adapters/*.c -c

test: test.c 
	$(CC) $(CFLAGS) test.c drive.c adapters/*.o obj/*.o -o test
