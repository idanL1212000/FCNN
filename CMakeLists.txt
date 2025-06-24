cmake_minimum_required(VERSION 3.24)
project(ex4_idanl2000)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex4_idanl2000
        Matrix.cpp
        Matrix.h Activation.h Activation.cpp main.cpp)
