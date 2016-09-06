# Search paths for the headers
include_directories(include
                    ../../modules/state_estimation/include)

# Source code running my code
set(HAL_LIB_SRCS
    ADC.cpp
    Control.cpp
    EEPROM.cpp
    GlobalVariables.cpp
    GPIO.cpp
    GPS.cpp
    HAL.cpp
    HC-SR04.cpp
    HMC5883L.cpp
    I2C.cpp
    MainLoop.cpp
    MPU6050.cpp
    MS5611.cpp
    Output.cpp
    pid.cpp
    RC.cpp
    SM_States.cpp
    SoftPWM.cpp
    StateMachine.cpp
    Telemetry.cpp
    Test.cpp
    Utils.cpp
)

generate_arduino_library(hal
    SRCS ${HAL_LIB_SRCS}
)

generate_arduino_firmware(${CMAKE_PROJECT_NAME}
      SRCS  ArduinoFC.cpp
      LIBS  hal state_estimation
      )
