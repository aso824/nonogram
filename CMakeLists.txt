cmake_minimum_required(VERSION 3.22)
project(nonogram)

set(CMAKE_CXX_STANDARD 23)

add_executable(nonogram main.cpp src/Nonogram.cpp src/Nonogram.h src/Grid.cpp src/Grid.h src/Loader/Loader.h src/Loader/FileLoader.cpp src/Loader/FileLoader.h src/Printer.cpp src/Printer.h)
