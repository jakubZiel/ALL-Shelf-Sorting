#include <iostream>

#include "algorithms/BruteForce.h"

int main() {


    std::vector<int> shelf = {2,2,3,3,3,3,3,3,3,2,0,3,2,2,2};


    BruteForce brute(shelf);

    auto result = brute.sort();


    brute.showStepByStep(result.moves);

    return 0;
}
