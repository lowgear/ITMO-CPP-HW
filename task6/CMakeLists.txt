cmake_minimum_required(VERSION 3.3)
project(task6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Test ${SOURCE_FILES})
add_library(lazy_string lazy_string.cpp)

target_link_libraries(Test lazy_string)

install(TARGETS lazy_string DESTINATION lib)
install(FILES lazy_string.h DESTINATION include)