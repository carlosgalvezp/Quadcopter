FROM ubuntu:16.04

ENV ARDUINO_VERSION 1.8.2
ENV ARDUINO_FILE arduino-$ARDUINO_VERSION-linux64.tar.xz

RUN apt-get update &&                               \
    apt-get install --assume-yes wget               \
                                 cmake              \
                                 gcc-avr            \
                                 binutils-avr       \
                                 avr-libc avrdude   \
                                 xz-utils           \
    && rm -rf /var/lib/apt/lists/*

RUN wget https://downloads.arduino.cc/$ARDUINO_FILE
RUN tar -xf $ARDUINO_FILE --directory /usr/share
