cmake_minimum_required(VERSION 3.23)
project(AED2223_GXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(AED2223_GXX main.cpp source/definitions/Graph.cpp source/headers/Graph.h source/definitions/Airport.cpp source/headers/Airport.h source/definitions/Airline.cpp source/headers/Airline.h source/definitions/Flight.cpp source/headers/Flight.h)
