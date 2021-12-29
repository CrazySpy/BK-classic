cmake_minimum_required(VERSION 3.20)
project(BK_classic)

set(CMAKE_CXX_STANDARD 14)

add_executable(BK_classic main.cpp BK.cpp BK.h Types.h EventClock/EventClock.hpp Utils.cpp Utils.h)
