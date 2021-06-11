//
// Created by jakub on 11.06.2021.
//

#ifndef SHELF_SORTING_BRUTEFORCE_H
#define SHELF_SORTING_BRUTEFORCE_H

#include <boost/container_hash/hash.hpp>
#include <queue>
#include <unordered_map>

struct node{
    std::vector<int> shelf;
    std::vector<int> moves;
};

class BruteForce {

    bool sorted = false;
    int visitedCount = 0;
    std::vector<int> shelf;
    std::queue<node> queue;
    std::unordered_map<size_t, node> visited;

    int counter[4]{0, 0, 0, 0};

    node bfs();
    static void move(std::vector<int>& shelfNode, int pos);

public:
    explicit BruteForce(size_t size);
    explicit BruteForce(std::vector<int> &shelf);

    node sort();
    bool isSorted(std::vector<int> &shelfNode);
    void showStepByStep(std::vector<int> &moves);
    static void printShelf(std::vector<int> &shelf);
    static void printIndicator(int pos, int size);
};


#endif //SHELF_SORTING_BRUTEFORCE_H
