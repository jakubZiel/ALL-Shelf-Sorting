//
// Created by jakub on 11.06.2021.
//

#ifndef SHELF_SORTING_BRUTEFORCE_H
#define SHELF_SORTING_BRUTEFORCE_H

#include <boost/container_hash/hash.hpp>
#include <queue>
#include <unordered_set>
#include <chrono>

struct node{
    std::vector<int> shelf;
    std::vector<int> moves;
};

class BruteForce {

    bool sorted = false;
    int visitedCount = 0;
    int queuedCount = 0;

    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;


    std::vector<int> shelf;
    std::queue<std::vector<int>> queue;
    std::unordered_set<size_t> visited;

    int counter[4]{0, 0, 0, 0};

    static void move(std::vector<int>& shelfNode, int pos);
    std::vector<int> bfs();

public:

    explicit BruteForce(size_t size);
    explicit BruteForce(std::vector<int> &shelf);

    void reset();
    void setShelf(std::vector<int> &newShelf);

    std::vector<int> sort();
    bool isSorted(std::vector<int> &shelfNode);
    void showStepByStep(std::vector<int> &moves);
    static void printShelf(std::vector<int> &shelf);
    static void printIndicator(int pos, int size);
    std::vector<int> restoreState(std::vector<int>& moves);

};


#endif //SHELF_SORTING_BRUTEFORCE_H
