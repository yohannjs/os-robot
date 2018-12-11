#!/bin/sh
echo "Kob-e make script"

arm-linux-gnueabi-gcc -std=c11 -Wall tests/logger.c interfaces/logger.c -o loggertest

echo "succ"
