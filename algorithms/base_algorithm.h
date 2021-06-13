#ifndef SHELF_SORTING_BASE_ALGORITHM_H
#define SHELF_SORTING_BASE_ALGORITHM_H
#include <vector>
class Base{
protected:
    int static const N = 4;
    std::vector<int> _shelf;
    int _shelf_size;
    int* _shelf_tab;
    int* _shelf_copy;
    int _counter[N];
    int _first_unsorted_index;
    int _find_color_pos(int color);
    std::vector<int> _moves_history;
    void _count_colors();
    void _show_single_step();
    void _print_indicator(int current_index);
public:
    Base(std::vector<int> &shelf);
    ~Base();
    void _move_to_beg(int color_first_occurrence_index);
    void _move(int color_first_occurrence_index);
    void _move_copy(int color_first_occurrence_index);
    virtual void sort() = 0;
    void show_step_by_step();
    std::vector<int> _get_move_history();
    std::vector<int> _get_sorted_shelf();
};
#endif //SHELF_SORTING_BASE_ALGORITHM_H