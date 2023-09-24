cmake_minimum_required(VERSION 3.24)
project(new_vignetting)

set(CMAKE_CXX_STANDARD 17)

add_executable(new_vignetting main.cpp parameter.cpp parameter.h function.cpp function.h)
