#!/bin/sh
echo "Building docker container..."
docker build -t kob-e .
echo "Running docker container...\n"
docker run kob-e
echo "\nDone (<:3"
