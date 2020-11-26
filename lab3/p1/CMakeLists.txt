cmake_minimum_required(VERSION 3.17)
project(p1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(p1
        main.cpp
        SudokuGrid.cpp
        SudokuGrid.h)
