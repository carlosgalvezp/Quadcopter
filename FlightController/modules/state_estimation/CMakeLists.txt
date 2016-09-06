include_directories(include
                    ../../core/include
                    ../../hal/arduino/include)

create_library(state_estimation
               SRCS
               Madgwick.cpp
               Mahony.cpp
               StateEstimation.cpp
               LIBS
               hal
)
