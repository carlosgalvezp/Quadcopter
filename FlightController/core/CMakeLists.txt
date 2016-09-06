# Search paths for the headers
include_directories(include
                    ../hal/arduino/include
                    ../modules/control/include
                    ../modules/state_estimation/include
                    ../modules/state_machine/include)

generate_arduino_firmware(${CMAKE_PROJECT_NAME}
      SRCS  ArduinoFC.cpp GlobalVariables.cpp MainLoop.cpp Test.cpp
      LIBS  control
            hal
            state_estimation
            state_machine
      )

