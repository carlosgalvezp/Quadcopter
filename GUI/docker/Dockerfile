FROM ubuntu:16.04

RUN apt-get update && \
    apt-get install --assume-yes build-essential \
                                 qt5-default \
                                 libqt5serialport5-dev

RUN rm -rf /var/lib/apt/lists/*
