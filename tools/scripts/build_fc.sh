#!/bin/bash
BUILD_DIR=build/Deploy
cd FlightController
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
../../../cmake-3.3.2-Linux-x86_64/bin/cmake ../.. -DCMAKE_TOOLCHAIN_FILE=../../cmake/ArduinoToolchain.cmake -DARDUINO_1_5=ON
make


