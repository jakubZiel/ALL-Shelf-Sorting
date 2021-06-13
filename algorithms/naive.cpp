#include "naive.h"
void Naive::sort(){
    for (int color = 0; color < N; color++){
        int color_count = _counter[color];
        for (int j=0; j<color_count; j++){
            _move_to_beg(_find_color_pos(color));
            _first_unsorted_index++;
        }
    }
}