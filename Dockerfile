FROM ev3dev/debian-jessie-cross

RUN sudo apt-get update && sudo apt-get install -y \
    libbluetooth-dev \
    libpng-dev \
    libsdl2-dev \
    libglew-dev


