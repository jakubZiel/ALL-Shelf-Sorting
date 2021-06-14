//
// Created by jakub on 12.06.2021.
//

#ifndef SHELF_SORTING_BENCHMARK_H
#define SHELF_SORTING_BENCHMARK_H

#include <chrono>
#include <vector>
#include "input_generator/input_generator.h"
#include <unordered_map>
#include <string>
#include "algorithms/base_algorithm.h"
#include <memory>
#include <map>
#include "algorithms/BruteForce.h"


enum Algorithm{
    BRUTE, BASIC, PATTERN, FAST
};

struct test_info{
    bool sorted = false;
    float calcTime = 0;
    float qValue = 0;
    std::vector<int> moves;
};

class Benchmark {

    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;

    // algorithms
    BruteForce bruteForce;

    std::unique_ptr<Base> baseAlgorithm;

    std::unordered_map<Algorithm, std::map<int, test_info>> results;
    std::vector<std::vector<int>> problems;

    std::vector<int> problemSizes;

    float calcQ(int medianN, Algorithm algorithm, int size);
    void test(Algorithm algorithm, std::vector<int> &shelf);
    static bool validate(std::vector<int> &shelf);
    void generateProblems(float probability);
    void calculateQuality();


    void printShelf(std::vector<int> &shelf);
    void printIndicator(int pos, int size);
    void move(std::vector<int>& shelfNode, int pos);

    void checkTestSteps();
    void readData();

public:
    Benchmark();

    void stepByStep(std::vector<int> &shelf, std::vector<int> &moves);
    void printTestInfo();
    void runUserInput();
    void runUser();
    void runTests(std::vector<int> &problemSizes, float probability);
    void runAuto(std::vector<int> &problemSizes, float probability);
};


#endif //SHELF_SORTING_BENCHMARK_H
