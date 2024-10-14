cmake_minimum_required(VERSION 3.23)
project(TransportesAereos)

set(CMAKE_CXX_STANDARD 11)

add_executable(TransportesAereos main.cpp code/Graph.cpp code/Graph.h code/Menu.cpp code/Menu.h code/Airport.cpp code/Airport.h code/Airline.cpp code/Airline.h code/Country.cpp code/Country.h code/City.cpp code/City.h code/DataSet.cpp code/DataSet.h code/Flight.cpp code/Flight.h)
