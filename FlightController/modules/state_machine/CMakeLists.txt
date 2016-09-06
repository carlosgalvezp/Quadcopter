include_directories(include
                    ../../core/include
                    ../../hal/arduino/include
                    ../control/include)

create_library(state_machine
               SRCS
               sm_state.cpp
               sm_state_armedacro.cpp
               sm_state_disarmed.cpp
               sm_state_passthrough.cpp
               sm_state_poweron.cpp
               StateMachine.cpp
               LIBS
               control
)
