# Use EV3 cross compilation platform as base
FROM ev3dev/debian-jessie-cross 

# Copy source code from host computer
COPY src . 

#RUN arm-linux-gnueabi-gcc lib/*.c -c

# Compile source code
#RUN arm-linux-gnueabi-gcc -Wall --std=c11 \
#    *.o \
#    main.c \
#    -o test

# Run source code
#CMD ["./test"]
