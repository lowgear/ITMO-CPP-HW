cmake_minimum_required(VERSION 3.3)
project(rationallib)

#add_library (Kek rational.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#target_include_directories (Kek PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES rational.h)
add_executable(rationallib ${SOURCE_FILES})
SET_TARGET_PROPERTIES(rationallib PROPERTIES LINKER_LANGUAGE C++)
