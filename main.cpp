#include <iostream>
#include "input_generator/input_generator.h"
#include "benchmark/Benchmark.h"
#include "algorithms/naive.h"


void test_input_generator(){
    InputGenerator inputGenerator(15);
    inputGenerator.gen_same_next(0.4);
    auto color_vector = inputGenerator.get_color_vector();
    for (int i = 0; i< 15; i++){
        std::cout<<color_vector[i];
    }
    std::cout << std::endl;
}

void test_benchmark(){

    Benchmark benchmark;

    std::vector<int> sizes = {100, 300, 500, 1000, 2000};

    float probability = 0.3f;

    benchmark.runUser();
}

void test_brute(){
    std::vector<int> shelf = {1,2,2,3,3,3,1,1,1,0,0,1,2,3,3,2,2,2,1,0};
    BruteForce bruteForce(shelf);
    bruteForce.sort();

}

int main() {
    test_brute();
    return 0;
}

