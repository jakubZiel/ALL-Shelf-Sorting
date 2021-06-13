/**
 * Slightly modified naive version. Takes grouped in 4 color first to the sorted part of shelf.
 */
#ifndef SHELF_SORTING_FOUR_FIRST_ALGORITHM_H
#define SHELF_SORTING_FOUR_FIRST_ALGORITHM_H
#include "base_algorithm.h"
class FourFirst: public Base{
    using Base::Base;
private:
    int _find_pattern(const int color, const int last_to_check_index);
public:
    void sort();
    void sort_2();

};
#endif //SHELF_SORTING_FOUR_FIRST_ALGORITHM_H
