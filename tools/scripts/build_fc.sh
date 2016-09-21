#!/bin/bash
BUILD_DIR=build/Deploy
cd FlightController
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
../../../cmake-3.3.2-Linux-x86_64/bin/cmake ../..
make


