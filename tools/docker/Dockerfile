FROM ubuntu:16.04

ENV ARDUINO_VERSION 1.8.3
ENV ARDUINO_FOLDER arduino-$ARDUINO_VERSION
ENV ARDUINO_TAR arduino-$ARDUINO_VERSION-linux64.tar.xz

WORKDIR /opt

RUN apt-get update && \
    apt-get install --assume-yes cmake \
                                 gcc-avr \
                                 binutils-avr \
                                 avr-libc \
                                 avrdude \
                                 tar \
                                 xz-utils \
                                 wget

RUN wget http://downloads.arduino.cc/$ARDUINO_TAR && \
    tar xf $ARDUINO_TAR && \
    rm $ARDUINO_TAR && \
    mv $ARDUINO_FOLDER /usr/local/share/arduino && \
    ln -s /usr/local/share/arduino/arduino /usr/local/bin/arduino

RUN apt-get remove --assume-yes xz-utils wget && \
    rm -rf /var/lib/apt/lists/*
