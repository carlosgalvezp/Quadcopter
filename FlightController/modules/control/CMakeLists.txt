include_directories(include
                    ../../hal/arduino/include)

create_library(control
               SRCS
               Control.cpp
               pid.cpp
)
