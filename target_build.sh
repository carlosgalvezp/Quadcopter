#!/bin/bash
cd FlightController
mkdir build
cd build
/opt/cmake-3.3.2-Linux-x86_64/bin/cmake .. -DARDUINO_TOOLCHAIN_FILE=../cmake/ArduinoToolchain.cmake -DARDUINO_1_5=ON
make
