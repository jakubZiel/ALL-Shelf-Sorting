#include "naive.h"
#include <iostream>
void Naive::sort(){
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