# Search paths for the headers
include_directories(../core/include
                    ../hal/arduino/include
                    ../modules/control/include
                    ../modules/state_estimation/include
                    ../modules/state_machine/include)

create_executable(${CMAKE_PROJECT_NAME}
      SRCS  main.cpp
      LIBS  control 
            core            
            hal
            state_estimation
            state_machine
      )


