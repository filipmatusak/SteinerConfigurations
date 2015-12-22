cmake_minimum_required(VERSION 3.3)
project(grafy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Reader.h BruteForcer.h common.h Verifier.h)
add_executable(grafy ${SOURCE_FILES})