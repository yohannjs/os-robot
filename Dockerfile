# Use EV3 cross compilation platform as base
FROM ev3dev/debian-jessie-cross 

# Update apt repo list
#RUN sudo apt-get update

# Copy source code from host computer
COPY src . 

#VOLUME src/bin ./bin

#RUN arm-linux-gnueabi-gcc lib/*.c -c

# Compile source code
#RUN arm-linux-gnueabi-gcc -Wall --std=c11 \
#    *.o \
#    main.c \
#    -o test

# Run source code
#CMD ["./test"]
