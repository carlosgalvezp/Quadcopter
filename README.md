# Quadcopter
Source code Quadcopter Flight Controller, based on Crius AIOP v2.0 (Atmega 2560)

# Ubuntu Instructions
-Run tools/scripts/
-Download Arduino SDK and extract under /usr/share

Build from QtCreator:

cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake/ArduinoToolchain.cmake -DARDUINO_1_5=ON

make

Permissions

To upload the code or to read from serial, we need some permissions
(http://playground.arduino.cc/Linux/All#Permission):

>> ls -l /dev/ttyUSB*

Note the group it belongs to (after root). For example: dialout.

>> sudo usermod -a -G <group_name> <username>


# Windows Instructions
-Qt Creator + MinGW
-Add the previous definitions
-MinGW Makefiles

Visual Studio - TO DO
