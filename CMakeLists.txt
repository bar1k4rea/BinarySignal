cmake_minimum_required(VERSION 3.20)
project(BinarySignal)

set(CMAKE_CXX_STANDARD 20)

add_executable(BinarySignal main.cpp dynamicLib/binarySignal.cpp dynamicLib/binarySignal.h)
