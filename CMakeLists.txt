cmake_minimum_required(VERSION 3.10)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator main.cpp calculator.cpp)
add_executable(test test.cpp calculator.cpp)
