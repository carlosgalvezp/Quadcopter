include_directories(${gtest_SOURCE_DIR}/include)

add_executable(test1 test1.cpp)
target_link_libraries(test1 gtest gtest_main)