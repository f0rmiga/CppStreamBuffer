cmake_minimum_required(VERSION 3.1)
project(CppStreamBuffer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CppStreamBuffer.hpp)
add_executable(CppStreamBuffer ${SOURCE_FILES})