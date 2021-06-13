//
// Created by jakub on 12.06.2021.
//

#include "algorithms/BruteForce.h"
#include "Benchmark.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

Benchmark::Benchmark(): bruteForce(0){
    for (int algorithm = BRUTE; algorithm <= FAST; algorithm++)
        results.insert(make_pair((Algorithm)algorithm, map<int, test_info>()));
}

bool Benchmark::validate(std::vector<int> &shelf) {

    int last = shelf[0];
    for (int i = 1; i < shelf.size(); ++i) {
        int current = shelf[i];
        if (current < last)
            return false;
        else if (current > last)
            last = current;
    }
    return true;
}

void Benchmark::test(Algorithm algorithm, std::vector<int> &shelf) {

    test_info info;
    vector<int> result;

    switch (algorithm) {

        case BRUTE:

            bruteForce = BruteForce(shelf);

            startTime = chrono::system_clock::now();
            info.moves = bruteForce.sort();

            endTime = chrono::system_clock::now();

            result = bruteForce.restoreState(info.moves);

            info.sorted = validate(result);

            break;

        case BASIC:
            startTime = chrono::system_clock::now();
            endTime = chrono::system_clock::now();
            break;

        case PATTERN:
            startTime = chrono::system_clock::now();
            endTime = chrono::system_clock::now();
            break;

        case FAST:
            startTime = chrono::system_clock::now();
            endTime = chrono::system_clock::now();
            break;

        default:
            break;
    }

    auto calculationTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
    info.calcTime = calculationTime.count();

    results[algorithm].insert(make_pair(shelf.size(), info));
}

void Benchmark::generateProblems(float probability) {


    for (auto& size : problemSizes){

        InputGenerator inputGenerator(size);
        inputGenerator.gen_same_next(probability);

        auto problem_uns = inputGenerator.get_color_vector();

        vector<int> problem(problem_uns.begin(), problem_uns.end());

        problems.push_back(problem);
    }
}

void Benchmark::runTests(vector<int> &_problemSizes, float probability){

    problemSizes =  _problemSizes;

    generateProblems(probability);

    for (int algorithm = BRUTE; algorithm <= FAST; algorithm++){

        for (auto problem : problems){

            test(Algorithm(algorithm), problem);

        }
    }

    calculateQuality();

    printTestInfo();

    checkTestSteps();
}

float Benchmark::calcQ(int medianN, Algorithm algorithm, int size) {

    float t_n = results[algorithm][size].calcTime;
    float t_median = results[algorithm][medianN].calcTime;

    float T_N;
    float T_median;

    if (algorithm == BRUTE){
        T_N = pow(4.0f, size);
        T_median = pow(4.0f, medianN);

    }else{
        T_N = pow(size, 3);
        T_median = pow(medianN, 3);
    }

    return (t_n * T_median) / (t_median * T_N);
}

void Benchmark::calculateQuality() {

    sort(problemSizes.begin(), problemSizes.end());

    int medianN;

    if (problemSizes.size() % 2 == 0)
        medianN = (problemSizes[problemSizes.size() / 2] + problemSizes[problemSizes.size() / 2  + 1]) / 2;
    else
        medianN = problemSizes[(problemSizes.size() + 1) / 2];

    for (int algorithm = BRUTE; algorithm <= FAST; algorithm++){

        for (int& size : problemSizes){

            auto algo = (Algorithm) algorithm;
            results[algo][size].qValue = calcQ(medianN, algo, size);
        }
    }
}

void Benchmark::printTestInfo(){

    for (int algorithm = BRUTE; algorithm <= FAST; algorithm++){

        if (algorithm == BRUTE)
            cout << "Brutal algorithm - O(4^n)" << endl;
        if (algorithm == BASIC)
            cout << "Basic algorithm - slow O(n^3)" << endl;
        if (algorithm == PATTERN)
            cout << "Pattern algorithm - faster O(n^3)" << endl;
        if (algorithm == FAST)
            cout << "Fast algorithm - fast O(n^3)" << endl;

        cout << "size   |   time    |   q   |   sorted   |   moves" << endl;

        for (auto beg = results[(Algorithm)algorithm].begin(); beg != results[(Algorithm)algorithm].end(); beg++){

            cout << beg->first << "   "  << beg->second.calcTime << "   "  << fixed << setprecision(2)  << beg->second.qValue << "   " << (beg->second.sorted ? "true" : "false") << "   " << beg->second.moves.size() << endl;
        }
        cout << endl << endl;
    }
}

void Benchmark::stepByStep(std::vector<int> &shelf, std::vector<int> &moves) {

    printShelf(shelf);

    for (auto currMove : moves){

        printIndicator(currMove, shelf.size());
        move(shelf, currMove);
        printShelf(shelf);
    }
}

void Benchmark::move(std::vector<int>& shelfNode, int pos){
    int size = shelfNode.size();

    int A, B, C, D;
    A = shelfNode[pos];
    B = shelfNode[pos + 1];
    C = shelfNode[pos + 2];
    D = shelfNode[pos + 3];

    for (int i = pos + 4; i < size; i++) {
        shelfNode[i - 4] = shelfNode[i];
    }

    shelfNode[size - 4] = A;
    shelfNode[size - 3] = B;
    shelfNode[size - 2] = C;
    shelfNode[size - 1] = D;
}

void Benchmark::printIndicator(int pos, int size) {
    for (int i = 0; i < size; i++){
        if (i == pos)
            std::cout << "^";
        else
            std::cout << " ";
    }

    std::cout << std::endl;
}

void Benchmark::printShelf(vector<int> &shelf) {
    for (auto element : shelf){
        cout << element;
    }

    cout << endl;
}

void Benchmark::checkTestSteps() {
    bool check = false;
    int algorithm;
    int size_index = 0;
    int size = 0;

    cout << "Do you want to check steps in test cases? (0/1)" << endl << endl;

    cin >> check;

    while(check) {

        std::cout << "Choose algorithm : BRUTE, BASIC, PATTERN, FAST (0,1,2,3)" << endl;

        cin >> algorithm;

        if (algorithm > 3)
            algorithm = 1;

        cout << "Choose problem size to test(index 0 : size - 1) : ";

        for (auto &s : problemSizes)
            cout << s << ", ";
        cout << endl;

        cin >> size_index;
        if (size_index > problemSizes.size() - 1 || size_index < 0)
            size_index = 0;

        size = problemSizes[size_index];


        vector<int> unsortedShelf = problems[size_index];
        vector<int>& moves = results[(Algorithm)algorithm][size].moves;

        stepByStep(unsortedShelf, moves);

        cout << endl << "Do you want to continue ? (0/1)" << endl;
        cin >> check;
    }
}

void Benchmark::runUserInput() {


}

void Benchmark::runUser(){

}


