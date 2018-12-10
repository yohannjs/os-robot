#!/bin/sh
case $1 in
    "crosscompile")
        echo "[DOCKER.SH] Building docker container..."
        docker build -t kob-e .
        echo "[DOCKER.SH] Running docker container...\n"
        docker run \
            kob-e \
            sh kobe.sh tests
        echo "\n[DOCKER.SH] Done (<:3"
        ;;
    *)
        echo "No params given.\n"
        echo "$0 crosscompile"
        echo "\tCompiles all code for brick and moves it to the bin directory."
esac
