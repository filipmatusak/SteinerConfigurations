cmake_minimum_required(VERSION 3.3)
project(grafy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/main/main.cpp
        src/main/Reader.h
        src/main/testers/BruteForcer.h
        src/main/testers/BruteForcer_C_10_6.h
        src/main/common.h
        src/main/Verifier.h
        src/main/testers/ColoringTester.cpp
        src/main/testers/ColoringTester.h
        src/main/ArgsParser.h
        src/main/tests/ColorTest.h
        src/main/tests/RemovabilityTest.h)
add_executable(grafy ${SOURCE_FILES})