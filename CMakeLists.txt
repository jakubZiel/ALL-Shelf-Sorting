cmake_minimum_required(VERSION 3.16)
project(Shelf_Sorting)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(Driver driver.cpp algorithms/BruteForce.cpp input_generator/input_generator.cpp benchmark/Benchmark.cpp
        algorithms/base_algorithm.cpp algorithms/four_first_algorithm.cpp algorithms/naive.cpp algorithms/space_sort.cpp
        )

add_executable(Shelf_Sorting main.cpp algorithms/BruteForce.cpp input_generator/input_generator.cpp benchmark/Benchmark.cpp
        algorithms/base_algorithm.cpp algorithms/four_first_algorithm.cpp algorithms/naive.cpp algorithms/space_sort.cpp
        )
