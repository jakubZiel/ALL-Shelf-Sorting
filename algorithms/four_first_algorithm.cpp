#include "four_first_algorithm.h"
#include <iostream>
#include <climits>
void FourFirst::sort_2(){
    std::cout<<"IN sort"<<std::endl;
    for (int i = 0; i < 4; i++){
        printf("%d", _counter[i]);
    }
    for (int color = 0; color < N; color++){
        std::cout<<"Color loop"<<std::endl;
        int color_count = _counter[color];
        for (int j=0; j<color_count; j++){
            std::cout<<"IN coutn loop"<<std::endl;
            _move_to_beg(_find_color_pos(color));
        }
    }
}
/**
 * Loop through the whole shelf looking for 4 consecutive instance of the same color. When found return index of the
 * first of them, if not found return -1.
 * @param color
 * @param last_to_check_index
 * @return
 */
int FourFirst::_find_pattern(const int color, const int last_to_check_index){
    for (int i = _first_unsorted_index, j = _counter[color]; i < _shelf_size; i++) {
        if (i > (last_to_check_index - 4) || i > (_shelf_size - 4) || j < 4)
            break;

        if (_shelf_tab[i] == color) {
            j--;

            if (_shelf_tab[i + 1] == color && _shelf_tab[i + 2] == color && _shelf_tab[i + 3] == color)
                return i;
        }
    }
    return  -1;
}

void FourFirst::sort(){
    int first_pattern_index, last_to_check_index;
    for (int i = 0; i < 3; i++) {
        last_to_check_index = _shelf_size;

        // search all paters for given color
        while ((first_pattern_index = _find_pattern(i, last_to_check_index)) != -1) {
            last_to_check_index -= 4;
            _move(first_pattern_index);
        }

        int moved = _shelf_size - last_to_check_index;


        if (last_to_check_index != _shelf_size) {
            // there was a pattern
            int unsorted_len = last_to_check_index - _first_unsorted_index;

            if (unsorted_len % 4 == 0) {
                for (int j = 0; j < unsorted_len / 4; j++) {
                    _move(_first_unsorted_index);
                }
            } else {
                for (int j = 0; j < unsorted_len / 4 + 1; j++) {
                    _move(_first_unsorted_index);
                }

                if (unsorted_len % 4 == 1) {
                    moved -= 3;
                } else if (unsorted_len % 4 == 2) {
                    moved -= 2;
                } else {
                    moved -= 1;
                }
            }
        }

        _first_unsorted_index += moved;
        _counter[i] -= moved;

        for (int j = 0; j < _counter[i]; j++) {
            _move_to_beg(_find_color_pos(i));
            _first_unsorted_index++;
        }
    }
}
