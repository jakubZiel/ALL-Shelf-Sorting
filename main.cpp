#include <iostream>
#include "algorithms/BruteForce.h"
#include "input_generator/input_generator.h"
#include "benchmark/Benchmark.h"

void test_brute_force(){
    std::vector<int> test = {3,0,0,0,3};

    std::vector<int> shelf = {2,2,3,3,3,3,3,3,3,2,0,3,2,2,2};

    std::vector<int> shelf1 = {1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0};

    std::vector<int> shelf2 = {1,3,3,1,1,1,1,1,0,0,3,1,1,1,1,1,1,1,3,2,2,1,3,3,3};

    std::vector<int> shelf3 = {0,3,3,0,1,1,2,3,3,3,3,3,1,1,3,3,2,0,0,2};

    std::vector<int> shelf4 = {1,3,3,1,0,3,2,3,2,3};



}
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

    std::vector<int> sizes = {7, 10, 12, 13, 14};

    float probability = 0.3f;

    benchmark.runTests(sizes, probability);
}

int main() {
    test_benchmark();
    return 0;
}

