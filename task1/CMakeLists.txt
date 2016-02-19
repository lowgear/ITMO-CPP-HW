cmake_minimum_required(VERSION 3.3)
project(task1)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c)
add_executable(task1 ${SOURCE_FILES})