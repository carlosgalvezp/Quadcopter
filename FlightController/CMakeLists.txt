cmake_minimum_required(VERSION 2.8)

project(FlightController)

include(cmake/utils.cmake)

# Compiler flags
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -O2 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Werror -std=c++11")

add_subdirectory(core)
add_subdirectory(hal)
add_subdirectory(modules)

# Build also tests if not compiling for Arduino
if (NOT CMAKE_TOOLCHAIN_FILE)
    if (MINGW)
        # https://cristianadam.eu/20151213/qtcreator-and-google-test/
        set (gtest_disable_pthreads on)
    endif()

    add_subdirectory(../common/3rdparty/googletest-master
        ${CMAKE_CURRENT_BINARY_DIR}/common/3rdparty/googletest-master)
	add_subdirectory(test)
endif()
