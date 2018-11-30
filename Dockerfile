FROM ev3dev/debian-jessie-cross 

COPY src . 

RUN make

CMD ["./wall-e"]
