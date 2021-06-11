//
// Created by jakub on 11.06.2021.
//

#ifndef SHELF_SORTING_BRUTEFORCE_H
#define SHELF_SORTING_BRUTEFORCE_H

#include <boost/container_hash/hash.hpp>
#include <queue>

class BruteForce {

    std::vector<int> shelf;
    std::queue<std::vector<int>> queue;
    std::map<int, std::vector<int>> visited;

    int counter[4]{0, 0, 0, 0};

    void bfs();
    void move(std::vector<int> shelfNode, int pos);

public:
    explicit BruteForce(size_t size);
    explicit BruteForce(std::vector<int> &shelf);

    void sort();
    bool isSorted(std::vector<int> &shelfNode);

};


#endif //SHELF_SORTING_BRUTEFORCE_H
