//
// Created by jakub on 13.06.2021.
//
#include <cstring>
#include "benchmark/Benchmark.h"
#include <iostream>
#include <vector>

int main(int argc, char **argv) {

    Benchmark benchmark;

    if (strcmp("-testing", argv[1]) == 0){

        std::vector<int> testSizes = {300, 400, 600, 800, 1000, 2000, 5000};
        float probability;

        int size;
        std::cout << "Do you want to use default test set {300, 400, 600, 800, 1000, 2000, 5000} (0/1)?" << std::endl;

        bool defaultSet;
        std::cin >> defaultSet;

        if (!defaultSet) {
            testSizes.clear();

            std::cout << "Choose test sizes, only unique sizes. (-1 to stop)." << std::endl;

            std::cin >> size;

            while (true) {
                if (size < 0)
                    break;
                else
                    testSizes.push_back(size);
                std::cin >> size;
            }
        }
        std::cout << "Choose probability of new element being identical to previous. (0. : 1.)" << std::endl;
        std::cin >> probability;

        benchmark.runTests(testSizes, probability);

    }else if (strcmp("-file", argv[1]) == 0){

        benchmark.runUserInput();

    }else if(strcmp("-user", argv[1]) == 0){

        benchmark.runUser();

    }else if(strcmp("-help", argv[1]) == 0){

        std::cout << "-auto     : user specifies : int startSize, int step, int howMany, float probability, then performance tests are ran" << std::endl;
        std::cout << "-user     : user specifies probability and problem size, then problem is generated" << std::endl;
        std::cout << "-file     : user inputs problems into data file, first line number of problems, then problems, and then algorithm type" << std::endl;
        std::cout << "-testing  : run all problems and tests performance, user specifies problems sizes and probability" << std::endl;
        std::cout << "-help     : list all possible modes" << std::endl;

    }else if (strcmp("-auto", argv[1]) == 0){

        int startSize = atoi(argv[2]);
        int step = atoi(argv[3]);
        int howMany = atoi(argv[4]);
        float probability = atof(argv[5]);

        std::vector<int> testSizes;

        int currentSize = startSize;

        for (int i = 0; i < howMany; i++){
            testSizes.push_back(currentSize);
            currentSize += step;
        }

        benchmark.runAuto(testSizes, probability);
    }else if (strcmp("-aggregate", argv[1]) == 0){

        int startSize = atoi(argv[2]);
        int step = atoi(argv[3]);
        int howMany = atoi(argv[4]);
        float probability = atof(argv[5]);

        int n = 10;

        std::vector<int> testSizes;

        int currSize = startSize;

        for (int i = 0; i < howMany; i++){
            testSizes.push_back(currSize);
            currSize += step;
        }


        std::vector<std::unordered_map<Algorithm, std::map<int, test_info>>> aggregation;
        for (int i = 0; i < n; i++){

            Benchmark neoBenchmark;
            neoBenchmark.runAuto(testSizes, probability);

            aggregation.push_back(std::unordered_map<Algorithm, std::map<int, test_info>>(neoBenchmark.results));
        }

        std::unordered_map<int, std::map<int, test_info>> final;


        for (int algorithm = BRUTE; algorithm <= FAST; algorithm++){
            for (int &size : testSizes){

                test_info aggregated;
                aggregated.calcTime = 0;
                aggregated.sorted = 0;
                aggregated.qValue = 0;
                aggregated.moveCount = 0;
                for (auto& test : aggregation){

                    aggregated.calcTime += test[(Algorithm)algorithm][size].calcTime;
                    aggregated.sorted += test[(Algorithm)algorithm][size].sorted;
                    aggregated.qValue += test[(Algorithm)algorithm][size].qValue;
                    aggregated.moveCount += test[(Algorithm)algorithm][size].moveCount;
                }

                aggregated.calcTime /= aggregation.size();
                aggregated.sorted /= aggregation.size();
                aggregated.qValue /= aggregation.size();
                aggregated.moveCount /= aggregation.size();

                final[algorithm][size] = aggregated;
            }
        }

        std::cout << "===============================================" << std::endl;

        Benchmark::printOuterResults(final);
    }




    return 0;
}

