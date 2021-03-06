#include <iostream>
#include "base_algorithm.h"

/**
 * Implement counter and basic functions needed for algorithms.
 */

Base::Base(std::vector<int> &shelf){
    _shelf = shelf;
    _shelf_size = shelf.size();
    _shelf_tab = new int[_shelf_size];
    _shelf_copy = new int[_shelf_size];
    _count_colors();
    _first_unsorted_index = 0;
}

Base::~Base(){
    delete[] _shelf_tab;
}
void Base::_count_colors() {
    for (int & i : _counter) {
        i = 0;
    }
    int j = 0;
    for (auto i : _shelf) {
        ++_counter[i];
        _shelf_tab[j] = i;
        _shelf_copy[j++] = i;
    }
}
int Base::_find_color_pos(int color) {
    int i = _first_unsorted_index;
    while (i < _shelf_size && _shelf_tab[i] != color)
        ++i;
    return i;
}
void Base::_move_to_beg(int color_first_occurrence_index) {
    _move_to_beg(color_first_occurrence_index, _first_unsorted_index);
}
void Base::_move_to_beg(int color_first_occurrence_index, int start_position){
    if (color_first_occurrence_index == start_position)
        return;

    int num = (_shelf_size - 1) - start_position;

    if (num > 6) {
        if ((color_first_occurrence_index - start_position) % 4 == 0) {
            for (int i = 0; i < (color_first_occurrence_index - start_position) / 4; i++) {
                _move(start_position);
            }
        } else {
            if (num % 4 == 0) {
                if (color_first_occurrence_index + 4 >= _shelf_size) {
                    _move(start_position);
                    color_first_occurrence_index -= 4;
                }

                if (color_first_occurrence_index - 3 < start_position) {
                    _move(color_first_occurrence_index);
                    color_first_occurrence_index = _shelf_size - 4;
                }

                _move(color_first_occurrence_index - 3);
                for (int i = 0; i < num / 4; i++) {
                    _move(start_position);
                }
            } else if (num % 4 == 1) {
                if (color_first_occurrence_index + 4 >= _shelf_size) {
                    _move(start_position);
                    color_first_occurrence_index -= 4;
                }

                if (color_first_occurrence_index - 2 < start_position) {
                    _move(color_first_occurrence_index);
                    color_first_occurrence_index = _shelf_size - 4;
                }

                _move(color_first_occurrence_index - 2);
                for (int i = 0; i < num / 4; i++) {
                    _move(start_position);
                }
            } else if (num % 4 == 2) {
                if (color_first_occurrence_index + 4 >= _shelf_size) {
                    _move(start_position);
                    color_first_occurrence_index -= 4;
                }

                if (color_first_occurrence_index - 1 < start_position) {
                    _move(color_first_occurrence_index);
                    color_first_occurrence_index = _shelf_size - 4;
                }

                _move(color_first_occurrence_index - 1);
                for (int i = 0; i < num / 4; i++) {
                    _move(start_position);
                }
            } else {
                if (color_first_occurrence_index + 4 >= _shelf_size) {
                    _move(start_position);
                    color_first_occurrence_index -= 4;
                }

                _move(color_first_occurrence_index);
                for (int i = 0; i < num / 4; i++) {
                    _move(start_position);
                }
            }
        }
    } else if (num == 6) {
        switch (color_first_occurrence_index - start_position) {
            case 1:
                _move(start_position);
                _move(start_position);

                break;

            case 2:
                _move(start_position);
                _move(start_position + 1);
                _move(start_position);
                _move(start_position);

                break;

            case 3:
                _move(start_position + 2);
                _move(start_position);

                break;

            case 4:
                _move(start_position);

                break;

            case 5:
                _move(start_position + 1);
                _move(start_position);
                _move(start_position);

                break;

            case 6:
                _move(start_position);
                _move(start_position);
                _move(start_position + 1);
                _move(start_position);
                _move(start_position);

                break;
            default:
                break;
        }
    } else if (num == 5) {
        switch (color_first_occurrence_index - start_position) {
            case 1:
                _move(start_position);
                _move(start_position + 1);
                _move(start_position);

                break;

            case 2:
                _move(start_position);
                _move(start_position);

                break;

            case 3:
                _move(start_position + 1);
                _move(start_position);

                break;

            case 4:
                _move(start_position);

                break;

            case 5:
                _move(start_position);
                _move(start_position);
                _move(start_position + 1);
                _move(start_position);

                break;
            default:
                break;
        }
    }
}
void Base::_move(int color_first_occurrence_index) {
    _moves_history.push_back(color_first_occurrence_index);
    int A, B, C, D;
    A = _shelf_tab[color_first_occurrence_index];
    B = _shelf_tab[color_first_occurrence_index + 1];
    C = _shelf_tab[color_first_occurrence_index + 2];
    D = _shelf_tab[color_first_occurrence_index + 3];

    for (int i = color_first_occurrence_index + 4; i < _shelf_size; i++) {
        _shelf_tab[i - 4] = _shelf_tab[i];
    }

    _shelf_tab[_shelf_size - 4] = A;
    _shelf_tab[_shelf_size - 3] = B;
    _shelf_tab[_shelf_size - 2] = C;
    _shelf_tab[_shelf_size - 1] = D;
}
void Base::_move_copy(int color_first_occurrence_index){
    int A, B, C, D;
    A = _shelf_copy[color_first_occurrence_index];
    B = _shelf_copy[color_first_occurrence_index + 1];
    C = _shelf_copy[color_first_occurrence_index + 2];
    D = _shelf_copy[color_first_occurrence_index + 3];

    for (int i = color_first_occurrence_index + 4; i < _shelf_size; i++) {
        _shelf_copy[i - 4] = _shelf_copy[i];
    }

    _shelf_copy[_shelf_size - 4] = A;
    _shelf_copy[_shelf_size - 3] = B;
    _shelf_copy[_shelf_size - 2] = C;
    _shelf_copy[_shelf_size - 1] = D;
};
void Base::_show_single_step() {
    std::string ret = "";
    for (int i = 0; i < _shelf_size; i++) {
        if (_shelf_tab[i] == 0)
            ret += "C";
        else if (_shelf_tab[i] == 1)
            ret += "M";
        else if (_shelf_tab[i] == 2) {
            ret += "Y";
        } else if (_shelf_tab[i] == 3) {
            ret += "K";
        }
    }
    std::cout << ret << std::endl;
}
void Base::_show_single_step_copy() {
    std::string ret = "";
    for (int i = 0; i < _shelf_size; i++) {
        if (_shelf_copy[i] == 0)
            ret += "C";
        else if (_shelf_copy[i] == 1)
            ret += "M";
        else if (_shelf_copy[i] == 2) {
            ret += "Y";
        } else if (_shelf_copy[i] == 3) {
            ret += "K";
        }
    }
    std::cout << ret << std::endl;
}
void Base::show_step_by_step() {
    int i = 0;
    _show_single_step_copy();
    for (auto pos : _moves_history) {
        _print_indicator(pos);
        _move_copy(pos);
        _show_single_step_copy();
    }
}

void Base::_print_indicator(int current_index){
    for (int i = 0; i < _shelf_size; i++){
        if (i == current_index)
            std::cout << "^";
        else
            std::cout << " ";
    }
    std::cout << std::endl;
}

std::vector<int> Base::_get_move_history() {
    return _moves_history;
}

std::vector<int> Base::_get_sorted_shelf() {

    std::vector<int> result(this->_shelf_tab, this->_shelf_tab + _shelf.size());
    return result;
}