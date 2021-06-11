#include <iostream>

#include "algorithms/BruteForce.h"

int main() {

    std::vector<int> test = {3,0,0,0,3};

    std::vector<int> shelf = {2,2,3,3,3,3,3,3,3,2,0,3,2,2,2};

    std::vector<int> shelf1 = {1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0};

    std::vector<int> shelf2 = {1,3,3,1,1,1,1,1,0,0,3,1,1,1,1,1,1,1,3,2,2,1,3,3,3};

    std::vector<int> shelf3 = {0,3,3,0,1,1,2,3,3,3,3,3,1,1,3,3,2,0,0,2};

    std::vector<int> shelf4 = {1,3,3,1,0,3,2,3,2,3};

    BruteForce brute(shelf);

    auto result = brute.sort();

    brute.showStepByStep(result);

    return 0;

}
