cmake_minimum_required(VERSION 3.17)
project(PM_examples)

#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17  -pthread" )
set(CMAKE_CXX_STANDARD_LIBRARIES -lpmemobj)
add_executable(PM_examples main.cpp pm_examples.hpp)