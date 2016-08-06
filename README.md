# Quadcopter
Source code Quadcopter Flight Controller, based on Crius AIOP v2.0 (Atmega 2560)

# Ubuntu Instructions
-Run tools/scripts/
-Download Arduino SDK and extract under /usr/share

Build:
cmake .. -DCMAKE_TOOLCHAIN_FILE=../common/ArduinoToolchain.cmake -DARDUINO_1_5=ON
make

# Windows Instructions
-Qt Creator + MinGW
-Add the previous definitions
-MinGW Makefiles

Visual Studio - TO DO
