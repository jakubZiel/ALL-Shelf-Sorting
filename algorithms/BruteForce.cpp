//
// Created by jakub on 11.06.2021.
//

#include "BruteForce.h"
#include <random>
using namespace std;
using namespace boost;

BruteForce::BruteForce(size_t size) {
    int value;


    for (int i = 0; i < size; i++){
        value = (int) random() % 4;
        counter[value]++;

        shelf.push_back(value);

    }
}

BruteForce::BruteForce(std::vector<int> &shelf) {
    this->shelf = shelf;

    for (int i : shelf)
        counter[i]++;
}


void BruteForce::bfs() {

    if (queue.empty()){
        return;
    }

    vector<int> current = queue.front();
    queue.pop();

    if (isSorted(current))
        return;

    for (int i = 0; i < current.size() - 4; i++){

    }

}


void BruteForce::sort() {

    queue.push(shelf);
    visited.insert({boost::hash_value(shelf), shelf});

    bfs();
}


bool BruteForce::isSorted(vector<int> &shelfNode) {

    int index = 0;
    for (int i = 0 ;i <= 3; i++){

        for (int j = 0; j < counter[i]; j++) {
            if (shelfNode[index] != i)
                return false;
            index++;
        }
    }

    return true;
}

void BruteForce::move(std::vector<int> shelfNode, int pos) {


}
