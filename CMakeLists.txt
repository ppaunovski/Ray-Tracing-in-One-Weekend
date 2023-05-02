cmake_minimum_required(VERSION 3.24)
project(Ray_Tracing_in_C__)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ray_Tracing_in_C__ source/main.cpp headers/vec3.h headers/color.h headers/ray.h)
