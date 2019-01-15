#   KOB-E Makefile
# By the KOB-E Squad

# All source code except for main and tests
src = $(wildcard src/interfaces/*.c) \
      $(wildcard src/adapters/*.c) \
      $(wildcard lib/*.c)

# List of all necessary object files
obj = $(src:.c=.o)

# List of test file executeables
exe_tst = $(patsubst tests/%.c, bin/%, $(wildcard tests/*.c))

# Header file includes
includes = -I./lib -I./src/interfaces -I./src/adapters -I./lib/ev3_link 

# Project wide defines
defines = -D _DEFAULT_SOURCE

# Other libraries
libraries = -lrt -lpthread -lev3dev-c

CC = arm-linux-gnueabi-gcc
CFLAGS = -O2 -g -std=gnu99 -W -Wall -Wno-comment $(includes) $(libraries) $(defines)

# Make both main file and tests if nothing else is specified
all: main tests
	
# Make main executeable
main: src/main.c $(obj) 
	$(CC) $(CFLAGS) $^ -o bin/$@

# Make test executeables 
tests: $(exe_tst)

# Pattern for making test files
bin/%_test: tests/%_test.c $(obj)
	$(CC) $(CFLAGS) $^ -o $@

# Removing ALL object files
clean:
	rm -f $(obj) 

