cmake_minimum_required(VERSION 3.6)
project(slotsgt_5x25)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp csv.cpp paytable.cpp symbolcount.cpp slotslogic.cpp)
add_executable(slotsgt_5x25 ${SOURCE_FILES})