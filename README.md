Quadcopter [![Build Status](https://travis-ci.org/carlosgalvezp/Quadcopter.svg?branch=master)](https://travis-ci.org/carlosgalvezp/Quadcopter)
==========
Source code Quadcopter Flight Controller, based on Crius AIOP v2.0 (Atmega 2560)

Ubuntu Instructions
-------------------
1. Run tools/scripts/setup_ubuntu.sh
2. Download Arduino SDK and extract under:

		/usr/share

3. Open CMakeLists.txt with QtCreator, with the following CMake arguments:

		-DCMAKE_TOOLCHAIN_FILE=cmake/ArduinoToolchain.cmake -DARDUINO_1_5=ON


### Loading firmware to Crius board

To upload the code or to read from serial, we need some permissions
(http://playground.arduino.cc/Linux/All#Permission):

1. With the board connected to the computer, run:

		ls - /dev/ttyUSB*

2. Note the group it belongs to (after root). For example: dialout.

3. Run the following command:

		sudo usermod -a -G <group_name> <username>
   Example:
		sudo usermod -a -G dialout carlos

Windows Instructions
--------------------
-Qt Creator + MinGW
-Add the previous definitions
-MinGW Makefiles

Visual Studio - TO DO
