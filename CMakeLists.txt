cmake_minimum_required(VERSION 3.17)
project(Shelf_Sorting)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(Shelf_Sorting main.cpp algorithms/BruteForce.cpp input_generator/input_generator.cpp benchmark/Benchmark.cpp)
