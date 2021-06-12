#include <iostream>
//#include "algorithms/BruteForce.h"
#include "input_generator/input_generator.h"
#include "algorithms/four_first_algorithm.h"
#include "algorithms/naive.h"
//void test_brute_force(){
//    std::vector<int> test = {3,0,0,0,3};
//
//    std::vector<int> shelf = {2,2,3,3,3,3,3,3,3,2,0,3,2,2,2};
//
//    std::vector<int> shelf1 = {1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0};
//
//    std::vector<int> shelf2 = {1,3,3,1,1,1,1,1,0,0,3,1,1,1,1,1,1,1,3,2,2,1,3,3,3};
//
//    std::vector<int> shelf3 = {0,3,3,0,1,1,2,3,3,3,3,3,1,1,3,3,2,0,0,2};
//
//    std::vector<int> shelf4 = {1,3,3,1,0,3,2,3,2,3};
//
//    BruteForce brute(shelf);
//
//    auto result = brute.sort();
//
//    brute.showStepByStep(result);
//}
void test_input_generator(){
    InputGenerator inputGenerator(15);
    inputGenerator.gen_same_next(0.8);
    auto color_vector = inputGenerator.get_color_vector();
//    for (int i = 0; i< 15; i++){
//        std::cout<<color_vector[i]<<std::endl;
//    }
}

int main() {
    test_input_generator();
    InputGenerator inputGenerator(20);
    inputGenerator.gen_same_next(0.8);
    auto color_vector = inputGenerator.get_color_vector();
//    Naive naive(color_vector);
//    naive.sort();
    FourFirst fourFirst(color_vector);
    fourFirst.sort();
    fourFirst.show_step_by_step();
    return 0;
}

