include_directories(include
                    ../../hal/arduino/include
                    ../control/include)

create_library(state_machine
               SRCS
               SM_States.cpp
               StateMachine.cpp
               LIBS
               control
)
