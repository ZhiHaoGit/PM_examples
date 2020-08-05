cmake_minimum_required(VERSION 3.17)
project(20200805)

#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17  -pthread" )
set(CMAKE_CXX_STANDARD_LIBRARIES -lpmemobj)
add_executable(20200805 main.cpp)