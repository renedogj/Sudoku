cmake_minimum_required(VERSION 3.29)
project(Sudoku)

set(CMAKE_CXX_STANDARD 20)

add_executable(Sudoku main.cpp
        Generate.cpp
        Generate.h
        SolveSudoku.cpp
        SolveSudoku.h
)
