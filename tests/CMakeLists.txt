cmake_minimum_required (VERSION 2.6)
project (ByteArray)

add_definitions ("-std=c++11 -O3 -g -Wall -fmessage-length=0")

find_package ( Boost 1.53 COMPONENTS context system REQUIRED )
include_directories ( ${Boost_INCLUDE_DIR} )

add_executable (main.o Main.cpp)

target_link_libraries (main.o "-lz" ${Boost_LIBRARIES})