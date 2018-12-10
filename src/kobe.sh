#!/bin/sh
if [ $1 = "crosscompile" ]; then
    echo "Cross compiling..."
    arm-linux-gnueabi-gcc -std=c11 -Wall -O2 \
        obj/*.o \
        adapters/detect.c \
        drive.c \
        tests/scan_test.c \
        -o scan_test
    echo "Done."
fi


