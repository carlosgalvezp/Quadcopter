FROM ubuntu:14.04

RUN apt-get update && \
    apt-get install -y tar xz-utils wget && \    
    wget http://downloads.arduino.cc/arduino-1.6.10-linux64.tar.xz && \
    tar xf arduino-1.6.10-linux64.tar.xz && \
    sudo mv arduino-1.6.10 /usr/local/share/arduino && \
    sudo ln -s /usr/local/share/arduino/arduino /usr/local/bin/arduino && \
    wget https://cmake.org/files/v3.3/cmake-3.3.2-Linux-x86_64.tar.gz && \
    tar zxf cmake-3.3.2-Linux-x86_64.tar.gz
