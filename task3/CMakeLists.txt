cmake_minimum_required(VERSION 3.3)
project(rationallib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library (rational rational.cpp)

set(SOURCE_FILES rational.cpp)

install(TARGETS rational DESTINATION "lib")
install(FILES rational.h DESTINATION "include")