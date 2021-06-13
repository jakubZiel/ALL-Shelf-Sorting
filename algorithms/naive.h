/**
 * Implementation of naive algorithm. Sort each color separately. Doesn't optimize for other colours.
 */
#ifndef SHELF_SORTING_NAIVE_H
#define SHELF_SORTING_NAIVE_H
#include "base_algorithm.h"
class Naive: public Base{
    using Base::Base;
public:
    void sort();

};
#endif //SHELF_SORTING_NAIVE_H
