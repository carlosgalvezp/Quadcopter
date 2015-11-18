project(OSDViewer)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

# OpenCV
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_LIST})

