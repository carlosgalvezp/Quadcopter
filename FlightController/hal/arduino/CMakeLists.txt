# Search paths for the headers
include_directories(include
                    ../../core/include)
                    #../../modules/state_estimation/include
                    #../../modules/state_machine/include)

create_library(hal
    SRCS
        ADC.cpp
        EEPROM.cpp
        GPIO.cpp
        GPS.cpp
        HAL.cpp
        HC-SR04.cpp
        HMC5883L.cpp
        I2C.cpp
        MPU6050.cpp
        MS5611.cpp
        Output.cpp
        RC.cpp
        SoftPWM.cpp
        Telemetry.cpp
        Utils.cpp
    LIBS
)
