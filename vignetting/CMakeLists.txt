cmake_minimum_required(VERSION 3.24)
project(vignetting)

set(CMAKE_CXX_STANDARD 17)

add_executable(vignetting main.cpp parameter.cpp parameter.h)
