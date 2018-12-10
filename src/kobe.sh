#!/bin/sh
case $1 in
    "tests")
        echo "Compiling..."
        arm-linux-gnueabi-gcc \
            -std=c11 \
            -Wall \
            -O2 \
            -D _BSD_SOURCE \
            obj/*.o \
            adapters/detect.c \
            drive.c \
            tests/scan_test.c \
            -o bin/scan_test \
            && echo "Compiling done."
        ;;
    *)
        echo "No args given, please feed me args."
esac

