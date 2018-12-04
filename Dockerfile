# Use EV3 cross compilation platform as base
FROM ev3dev/debian-jessie-cross 

# Update apt repo list
RUN sudo apt-get update

# Copy source code from host computer
COPY src . 

# Compile source code
RUN make

# Run source code
CMD ["./wall-e"]
