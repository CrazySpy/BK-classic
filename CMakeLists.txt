cmake_minimum_required(VERSION 3.20)
project(BK_classic)

set(CMAKE_CXX_STANDARD 14)

add_executable(BK_classic main.cpp BK.cpp BK.h Types.h DistanceStrategy.h EuclidDistanceStrategy.cpp EuclidDistanceStrategy.h Utils.cpp Utils.h CSVReader/CSVReader.h CSVReader/CSVReader.cpp EventClock/EventClock.hpp)
