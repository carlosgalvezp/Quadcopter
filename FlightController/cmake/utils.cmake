if (DEFINED ARDUINO_1_5)

    # The Arduino variant
    set(ARDUINO_DEFAULT_BOARD mega)
    # The ttyport for writing to the Arduino
    set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0)

    set(mega.build.mcu atmega2560)
    set(mega.upload.protocol wiring)
    set(mega.upload.speed 115200)

endif()

function(create_library lib_name)
    cmake_parse_arguments(create_library "" "" "SRCS;LIBS" ${ARGN})

    if (DEFINED ARDUINO_1_5)
        generate_arduino_library(${lib_name}
            SRCS ${create_library_SRCS}
            LIBS ${create_library_LIBS}
        )
    endif()
endfunction(create_library)

function(create_executable executable_name)
    cmake_parse_arguments(create_executable "" "" "SRCS;LIBS" ${ARGN})

    if (DEFINED ARDUINO_1_5)
        generate_arduino_firmware(${executable_name}
            SRCS ${create_executable_SRCS}
            LIBS ${create_executable_LIBS}
        )
    endif()
endfunction(create_executable)
