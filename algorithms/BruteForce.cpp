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

node BruteForce::bfs() {


    if (queue.empty()){
        node empty;
        return empty;
    }

    node current = queue.front();
    queue.pop();

    if (isSorted(current.shelf)){
        sorted = true;
        return current;
    }

    for (int pos = 0; pos < current.shelf.size() - 4; pos++){


        node newNode = current;
        newNode.moves.push_back(pos);

        move(newNode.shelf, pos);

        if (visited.find(hash_value(newNode.shelf)) == visited.end()){
            visited.insert({hash_value(newNode.shelf), newNode});
            queue.push(newNode);
        }
    }

    return bfs();
}

node BruteForce::sort() {


    node root;
    root.shelf = shelf;
    root.moves.clear();

    queue.push(root);
    visited.insert({boost::hash_value(root.shelf), root});

    return bfs();
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
    cout << "visited configurations : " << visited.size() << endl;
    cout << "calculation time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << endl;

    printShelf(shelf);

    for (auto currMove : moves){

        printIndicator(currMove, shelf.size());
        move(shelf, currMove);
        printShelf(shelf);
    }
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
