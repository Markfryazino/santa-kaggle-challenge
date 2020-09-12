cmake_minimum_required(VERSION 3.15)
project(genetic)

set(CMAKE_CXX_STANDARD 17)

add_executable(genetic main.cpp Distribution.h Distribution.cpp Population.cpp Population.h funcs.cpp funcs.h)