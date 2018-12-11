# Use EV3 cross compilation platform as base
FROM ev3dev/debian-jessie-cross 

# Copy source code from host computer
COPY src . 

#RUN arm-linux-gnueabi-gcc lib/*.c -c

# Compile source code
RUN arm-linux-gnueabi-gcc --std=c11 -Wall -lrt -pthread \
    adapters/cake.c \ 
    test.c \
    -o test

# Run source code
#CMD ["./test"]
