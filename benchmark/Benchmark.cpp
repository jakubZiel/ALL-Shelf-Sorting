//
// Created by jakub on 12.06.2021.
//

#include "algorithms/BruteForce.h"
#include "Benchmark.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "algorithms/four_first_algorithm.h"
#include "algorithms/naive.h"
#include "algorithms/space_sort.h"
#include <numeric>


using namespace std;

Benchmark::Benchmark(): bruteForce(0), _data{
        {BRUTE, {}}, {BASIC, {}}, {PATTERN, {}}, {FAST, {}}}
{

    for (int algorithm = BRUTE; algorithm <= FAST; algorithm++) {
        results.insert(make_pair((Algorithm) algorithm, map<int, test_info>()));
    }
    input_generators_initialized = false;
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

    if (algorithm == BRUTE){

        if (shelf.size() < 20){
            bruteForce = BruteForce(shelf);

            startTime = chrono::system_clock::now();
            info.moves = bruteForce.sort();

            endTime = chrono::system_clock::now();

            result = bruteForce.restoreState(info.moves);

            info.sorted = validate(result);
        }
    }else{

        switch (algorithm) {
            case BASIC:
                baseAlgorithm = make_unique<Naive>(shelf);
                break;
            case PATTERN:
                baseAlgorithm = make_unique<FourFirst>(shelf);
                break;
            case FAST:
                baseAlgorithm = make_unique<SpaceSort>(shelf);
                break;
            default:
                break;
        }

        startTime = chrono::system_clock::now();
        baseAlgorithm->sort();
        endTime = chrono::system_clock::now();

        info.moves = baseAlgorithm->_get_move_history();
        result = baseAlgorithm->_get_sorted_shelf();
        info.sorted = validate(result);

    }

    auto calculationTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
    info.calcTime = calculationTime.count();

    results[algorithm].insert(make_pair(shelf.size(), info));
}
void Benchmark::initialize_input_generators() {
    if (input_generators_initialized == true)
        return;
    for (auto problem_size: problemSizes){
        input_generators[problem_size] = new InputGenerator(problem_size);
    }
    input_generators_initialized = true;
}
void Benchmark::generateProblems(float probability) {


    for (auto& size : problemSizes){
        initialize_input_generators();
        input_generators[size]->gen_same_next(probability);

        auto problem_uns = input_generators[size]->get_color_vector();

        vector<int> problem(problem_uns.begin(), problem_uns.end());

        problems.push_back(problem);
    }
}

void Benchmark::runTests(vector<int> &_problemSizes, float probability){

    runAuto(_problemSizes, probability, 1);

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
        medianN = problemSizes[(problemSizes.size() ) / 2];

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

        cout << "size   |   time    |   q   |   sorted   |   moves" << endl << endl;

        for (auto beg = results[(Algorithm)algorithm].begin(); beg != results[(Algorithm)algorithm].end(); beg++){

            cout << beg->first << "   "  << fixed << setprecision(0) << beg->second.calcTime << "   "  << fixed << setprecision(2)
            << beg->second.qValue << "   " << (beg->second.sorted ? "true" : "false") << "   " << beg->second.moves.size() << endl;
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
    readData();

    string algorithm_s;
    Algorithm algorithm;
    test_info info;

    cin >> algorithm_s;

    if (algorithm_s == "BRUTE")
        algorithm = BRUTE;

    if (algorithm_s == "BASIC")
        algorithm = BASIC;

    if (algorithm_s == "PATTERN")
        algorithm = PATTERN;

    if (algorithm_s == "FAST")
        algorithm = FAST;


    vector<int> result;

    for (auto &problem : problems){

        if (algorithm == BRUTE){

            bruteForce = BruteForce(problem);
            info.moves = bruteForce.sort();
        }else{
            switch (algorithm){
                case BASIC:
                    baseAlgorithm = make_unique<Naive>(problem);
                    break;
                case PATTERN:
                    baseAlgorithm = make_unique<FourFirst>(problem);
                    break;
                case FAST:
                    baseAlgorithm = make_unique<SpaceSort>(problem);
                    break;
                default:
                    break;
            }

            baseAlgorithm->sort();
            info.moves = baseAlgorithm->_get_move_history();
        }

        results[algorithm].insert(make_pair(problem.size(), info));
    }

    for (auto &problem : problems){

        stepByStep(problem, results[algorithm][problem.size()].moves);
        cout << endl << endl;

    }

}

void Benchmark::runUser(){


    float probability;
    int size;
    int algorithm;

    std::cout << "Input probability of next element being same as previous one.(0. : 1.) :" << endl;
    cin >> probability;

    if (probability < 0 || probability > 1)
        probability = 0.3;

    std::cout << "Input size of test example : " << endl;
    cin >> size;

    if (size < 0)
        size = 15;

    problemSizes.push_back(size);
    generateProblems(probability);


    std::cout << "Input algorithm type : BRUTE, BASIC, PATTERN, FAST (0,1,2,3)" << endl;
    cin >> algorithm;

    if (algorithm > 3 || algorithm < 0)
        algorithm = 1;

    vector<int> moves;

    if (algorithm == BRUTE){
        bruteForce = BruteForce(problems[0]);
        moves = bruteForce.sort();
    }else {

        switch (algorithm) {
            case BASIC:
                baseAlgorithm = make_unique<Naive>(problems[0]);
                break;
            case PATTERN:
                baseAlgorithm = make_unique<FourFirst>(problems[0]);
                break;
            case FAST:
                baseAlgorithm = make_unique<SpaceSort>(problems[0]);
                break;
        }

        baseAlgorithm->sort();
        moves = baseAlgorithm->_get_move_history();
    }

    cout << "Correction check : " << endl;

    stepByStep(problems[0], moves);
}

void Benchmark::readData() {

    vector<int> problem;

    int numberOfProblems;
    string shelf;

    cin >> numberOfProblems;

    for (int i = 0; i < numberOfProblems; i++){

        cin >> shelf;

        for (char c : shelf){

            int element = atoi(&c);
            problem.push_back(element);
        }
        problems.push_back(problem);
        problemSizes.push_back(problem.size());
        problem.clear();
    }
}

void Benchmark::runAuto(std::vector<int> &_problemSizes, float probability, int repetitions) {

    problemSizes =  _problemSizes;
    for (int i = 0; i< repetitions; i++){
        generateProblems(probability);
        for (int algorithm = BRUTE; algorithm <= FAST; algorithm++){

            for (auto problem : problems){

                test(Algorithm(algorithm), problem);

            }
        }
        calculateQuality();
        saveData();
    }
    calculateStatistics();
    displayStatistics();
}

/**
 * Calculates mean and std for time and qValue. Data comes from many runs of the program.
 */
void Benchmark::calculateStatistics() {
    for (auto problem_size: problemSizes){
        for (int algorithm = BRUTE; algorithm < FAST+1; algorithm++){
            std::vector<string> d_types = {"time", "qvalue"};
            for (auto d_type: d_types){
                auto data_vector = _data[static_cast<Algorithm>(algorithm)][problem_size][d_type];
                float sum = std::accumulate(data_vector.begin(), data_vector.end(), 0.0);
                float mean = sum / data_vector.size();
                float sq_sum = std::inner_product(data_vector.begin(), data_vector.end(), data_vector.begin(), 0.0);
                float stdev = std::sqrt(sq_sum / data_vector.size() - mean * mean);
                _statistics[static_cast<Algorithm>(algorithm)][problem_size]["mean_"+d_type]=mean;
                _statistics[static_cast<Algorithm>(algorithm)][problem_size]["std_"+d_type]=stdev;
            }
        }
    }
}
/**
 * Saves data after one run of sorting for all algorithms.
 */
void Benchmark::saveData() {
    for (auto problem_size: problemSizes){
        for (int algorithm = BRUTE; algorithm < FAST+1; algorithm++){
            _data[static_cast<Algorithm>(algorithm)][problem_size]["time"].
            push_back(results[static_cast<Algorithm>(algorithm)][problem_size].calcTime);
            _data[static_cast<Algorithm>(algorithm)][problem_size]["qvalue"].
            push_back(results[static_cast<Algorithm>(algorithm)][problem_size].qValue);
        }
    }



}
void Benchmark::displayStatistics() {
    for (int algorithm = BRUTE; algorithm <= FAST; algorithm++){

        if (algorithm == BRUTE)
            cout << "Brutal algorithm - O(4^n)" << endl;
        if (algorithm == BASIC)
            cout << "Basic algorithm - slow O(n^3)" << endl;
        if (algorithm == PATTERN)
            cout << "Pattern algorithm - faster O(n^3)" << endl;
        if (algorithm == FAST)
            cout << "Fast algorithm - fast O(n^3)" << endl;

        cout << "size   |   mean_time    |   std_time   |   mean_qvalue   |   std_qvalue" << endl << endl;

        for (auto statistics = _statistics[static_cast<Algorithm>(algorithm)].begin(); statistics != _statistics[static_cast<Algorithm>(algorithm)].end(); statistics++){

            cout << statistics->first << "   "  << fixed << setprecision(0) <<
            statistics->second["mean_time"]<< "   "  << fixed << setprecision(0)<< statistics->second["std_time"] << "   "
            << fixed << setprecision(2)<< statistics->second["mean_qvalue"]<<
            fixed << setprecision(2)<< "   " << statistics->second["std_qvalue"] << endl;
        }
        cout << endl << endl;
    }
}



