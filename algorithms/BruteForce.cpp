//
// Created by jakub on 11.06.2021.
//

#include "BruteForce.h"
#include <random>
#include <iostream>
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

vector<int> BruteForce::bfs() {
    vector<int> root;

    queue.push(root);
    queuedCount++;
    visitedCount++;
    visited.insert({boost::hash_value(shelf)});


    while(!queue.empty()){

        vector<int> current = queue.front();
        queue.pop();
        queuedCount--;

        vector<int> currentShelfState = restoreState(current);

        if (isSorted(currentShelfState)){
            sorted = true;
            return current;
        }

        for (int pos = 0; pos < currentShelfState.size() - 4; pos++){

            vector<int> newNode = current;
            newNode.push_back(pos);

            vector<int> newShelfState = restoreState(newNode);

            if (visited.find(hash_value(newShelfState)) == visited.end()){
                visited.insert({hash_value(newShelfState)});
                queue.push(newNode);
                visitedCount++;
                queuedCount++;
            }
        }
    }

    vector<int> notFound;
    return notFound;
}

vector<int> BruteForce::sort() {

    startTime = std::chrono::system_clock::now();

    auto result = bfs();

    endTime = std::chrono::system_clock::now();

    return result;
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

void BruteForce::move(std::vector<int>& shelfNode, int pos) {
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


void BruteForce::showStepByStep(vector<int> &moves) {

}

void BruteForce::printShelf(vector<int> &shelf){

    for (auto element : shelf){
        cout << element;
    }

    cout << endl;
}

void BruteForce::printIndicator(int pos, int size){
    for (int i = 0; i < size; i++){
        if (i == pos)
            std::cout << "^";
        else
            std::cout << " ";
    }

    std::cout << std::endl;
}

vector<int> BruteForce::restoreState(vector<int> &moves) {

    vector<int> restored = shelf;

    for (auto currMove : moves){
        move(restored, currMove);
    }

    return restored;
}

void BruteForce::reset(){

    sorted = false;
    visitedCount = 0;
    queuedCount = 0;

    visited.clear();

    std::queue<vector<int>> empty;
    queue.swap(empty);

    shelf.clear();

    for (int & i : counter)
        i = 0;
}

void BruteForce::setShelf(vector<int> &newShelf) {

    reset();

    shelf = newShelf;

    for (int i : shelf)
        counter[i]++;
}

bool BruteForce::getSorted() {
    return sorted;
}