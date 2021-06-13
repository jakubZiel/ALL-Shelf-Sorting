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

        std::vector<int> testSizes;
        float probability;

        int size;
        std::cout << "Choose test sizes, only unique sizes. (-1 to stop)." << std::endl;

        std::cin >> size;

        while(true){

            if (size < 0)
                break;
            else
                testSizes.push_back(size);
            std::cin >> size;
        }

        std::cout << "Choose probability of new element being identical to previous. (0. : 1.)" << std::endl;
        std::cin >> probability;

        benchmark.runTests(testSizes, probability);

    }else if (strcmp("-file", argv[1]) == 0){

        benchmark.runUserInput();

    }else if(strcmp("-user", argv[1]) == 0){

        benchmark.runUser();

    }
    return 0;
}

