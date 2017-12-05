cmake_minimum_required(VERSION 3.8)
project(ass1)

set(CMAKE_CXX_STANDARD 98)



set(SOURCE_FILES main.cpp Server.cpp Server.h)
add_executable(ass1 ${SOURCE_FILES})

