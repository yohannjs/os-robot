CC=arm-linux-gnueabi-gcc
CFLAGS=-Wall -std=c11 -O2

EV3=lib/*.o

INCLUDES=-I./lib/ -I./src/interfaces/ -I./src/adapters/

all: main drive_test detect_test

# Main executeable
main: src/main.c src/interfaces/detect.o src/interfaces/drive.o src/adapters/navigate.o
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(EV3) -o bin/$@

# Tests
drive_test: tests/drive_test.c src/interfaces/drive.o
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(EV3) -o bin/$@

detect_test: tests/detect_test.c src/interfaces/detect.o
	$(CC) $(CLFAGS) $(INCLUDES) $^ $(EV3) -o bin/$@

# Modules
detect.o: src/interfaces/detect.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -c -o src/interfaces/$@

drive.o: src/interfaces/drive.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -c -o src/interfaces/$@

navigate.o: src/adapters/navigate.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -c -o src/adapters/$@

lib/%.o: lib/%.c
	$(CC) $(CFLAGS) lib/$*.c -c lib/$*.o 

lib: lib/%.o 
	ar c lib/ev3.a $^

# Cleaning
clean:
	rm src/interfaces/*.o src/adapters/*.o

