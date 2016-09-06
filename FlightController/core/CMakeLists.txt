# Search paths for the headers
include_directories(include
                    ../hal/arduino/include
                    ../modules/control/include
                    ../modules/state_estimation/include
                    ../modules/state_machine/include)

create_library(core
      SRCS  ArduinoFC.cpp GlobalVariables.cpp MainLoop.cpp Test.cpp
      LIBS  control
            hal
            state_estimation
            state_machine
      )

