cmake_minimum_required(VERSION 3.8)
project(polynomials)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/Monom.cpp include/Monom.h src/Polynom.cpp include/Polynom.h)
add_executable(polynomials ${SOURCE_FILES})