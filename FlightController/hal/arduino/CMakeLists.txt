# CMake Configuration for an Arduino project
#

print_board_list()
print_programmer_list()

# The Arduino variant
set(ARDUINO_DEFAULT_BOARD mega)
# The ttyport for writing to the Arduino
set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0)

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
include_directories(include)

# Source code running my code
set(CODE_SRCS
    ADC.cpp
    ArduinoFC.cpp
    Control.cpp
    EEPROM.cpp
    GlobalVariables.cpp
    GPIO.cpp
    GPS.cpp
    HAL.cpp
    HC-SR04.cpp
    HMC5883L.cpp
    I2C.cpp
    Madgwick.cpp
    Mahony.cpp
    MainLoop.cpp
    MPU6050.cpp
    MS5611.cpp
    Output.cpp
    pid.cpp
    RC.cpp
    SM_States.cpp
    SoftPWM.cpp
    StateEstimation.cpp
    StateMachine.cpp
    Telemetry.cpp
    Test.cpp
    Utils.cpp
)

generate_arduino_firmware(${CMAKE_PROJECT_NAME}
      SRCS  ${CODE_SRCS}
      HDRS  ${LIBRARY_HDRS}
      )
