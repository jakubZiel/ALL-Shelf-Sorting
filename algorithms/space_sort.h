#ifndef SHELF_SORTING_SPACE_SORT_H
#define SHELF_SORTING_SPACE_SORT_H
#include "base_algorithm.h"
class SpaceSort: public Base{
    using Base::Base;
private:
    void _make_spaces(const int color);
    int _find_other_color_pos(const int color) const;
public:
    void sort();

    void _move_other_to_end(const int color, const int pos);

    void _move_other_from_end(const int color, const int pos);

    void _move_from_end(const int color, const int pos);
};
#endif //SHELF_SORTING_SPACE_SORT_H
