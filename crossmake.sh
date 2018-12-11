#!/bin/sh
echo "\nKOB-E CROSS COMPILER\n"
echo "Starting docker container..."
docker run --name kob-e -v $(pwd):/home/compiler -w /home/compiler \
    ev3dev/debian-jessie-cross \
    make $1
echo "Docker container finished, cleaning up..."
docker rm kob-e
echo "Docker container removed. Done."

