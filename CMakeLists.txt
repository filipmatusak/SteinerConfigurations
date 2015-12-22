cmake_minimum_required(VERSION 3.3)
project(grafy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main/main.cpp src/main/Reader.h src/main/testers/BruteForcer.h src/main/common.h src/main/Verifier.h)
add_executable(grafy ${SOURCE_FILES})