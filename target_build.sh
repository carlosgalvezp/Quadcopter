#!/bin/bash
cd FlightController
mkdir build
cd build
cmake .. -DARDUINO_TOOLCHAIN_FILE=../cmake/ArduinoToolchain.cmake -DARDUINO_1_5=ON
make
