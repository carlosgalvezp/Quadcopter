# CMake Configuration for an Arduino project
#
cmake_minimum_required(VERSION 2.8)

set(CMAKE_TOOLCHAIN_FILE 3rdparty/arduino-cmake-master/cmake/ArduinoToolchain.cmake) # Arduino Toolchain
set(ARDUINO_1_5 True)

project(Quadcopter)

print_board_list()
print_programmer_list()

# The Arduino variant
set(ARDUINO_DEFAULT_BOARD mega)
# The ttyport for writing to the Arduino
set(ARDUINO_DEFAULT_PORT /dev/tty.usbserial-A6024Z1X)

set(mega.build.mcu atmega2560)
set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)

# Add library paths or alternatively in the CODE_SRCS variable
set(LIBRARY_SRCS
)

# Additional Headers
set(LIBRARY_HDRS
)

# Search paths for the headers
include_directories(ArduinoFC)

# Source code running my code
set(CODE_SRCS
    ArduinoFC/ADC.cpp
    ArduinoFC/ArduinoFC_2.cpp
    ArduinoFC/Control.cpp
    ArduinoFC/EEPROM.cpp
    ArduinoFC/GlobalVariables.cpp
    ArduinoFC/GPIO.cpp
    ArduinoFC/GPS.cpp
    ArduinoFC/HAL.cpp
    ArduinoFC/HC-SR04.cpp
    ArduinoFC/HMC5883L.cpp
    ArduinoFC/I2C.cpp
    ArduinoFC/Madgwick.cpp
    ArduinoFC/Mahony.cpp
    ArduinoFC/MainLoop.cpp
    ArduinoFC/MPU6050.cpp
    ArduinoFC/MS5611.cpp
    ArduinoFC/Output.cpp
    ArduinoFC/pid.cpp
    ArduinoFC/RC.cpp
    ArduinoFC/SM_States.cpp
    ArduinoFC/SoftPWM.cpp
    ArduinoFC/StateEstimation.cpp
    ArduinoFC/StateMachine.cpp
    ArduinoFC/Telemetry.cpp
    ArduinoFC/Test.cpp
    ArduinoFC/Utils.cpp
)

generate_arduino_firmware(${CMAKE_PROJECT_NAME}
      SRCS  ${CODE_SRCS}
      HDRS  ${LIBRARY_HDRS}
      )
