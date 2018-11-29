FROM ev3dev/debian-jessie-cross 

COPY src src

RUN arm-linux-gnueabi-gcc -Wall -o wall-e src/main.c

CMD ["./wall-e"]
