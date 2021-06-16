#include "space_sort.h"
/**
 * Each sort starts with making groups of multiple of 4 and then normal sorting.
 */
void SpaceSort::sort() {
    for (int i = 0; i < 3; i++) {
        if (_counter[i] > 6) {
            _make_spaces(i);
        }
        else { // normal 'naive' sorting
            for (int j = 0; j < _counter[i]; ++j) {
                _move_to_beg(_find_color_pos(i));
                ++_first_unsorted_index;
            }
        }
    }
}
/**
 * Create groups of size  n * 4, where n is natural number of color other than currently being sorted.
 * Move the created group to the end of shelf.
 * Proposed heuristic provides more sorted (and grouped) next colors therefore decreases moves necessary for sorting.
 * @param color currently sorted color
 */
void SpaceSort::_make_spaces(const int color) {
    // number of unsorted elements after current color will be sorted
    // so for clarity it's also can be though as number of different color elements that haven't be sorted yet
    // for C it will be number of elements of M Y K
    // fo r M it will be number of elements of Y K
    // for Y it will be number of K elements
    int different_color_unsorted_elem = _shelf_size - _first_unsorted_index - this->_counter[color];
    //number of different color elements sorted in preprocessing
    int n = 0;
    int tmp = _first_unsorted_index;
    // preprocess shelf the way that you will know that after the sorting phase there will be multiple of 4 number of unsorted elements
    // note that we move _fist_unsorted_index even if we don't sort shelf, but move 'other color' to sorted part
    // amend to that preprocessing step will be done at the end
    if (different_color_unsorted_elem % 4 == 1) {
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        n += 3;
        different_color_unsorted_elem -= 1;
    } else if (different_color_unsorted_elem % 4 == 2) {
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        n += 2;
        different_color_unsorted_elem -= 2;
    } else if (different_color_unsorted_elem % 4 == 3) {
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        n += 1;
        different_color_unsorted_elem -= 3;
    }
    //preprocessing done

    // group elements of different color than the one being sorted into groups of size multiple of 4
    int counter;//number of element of color different grouped together
    for (int i = _first_unsorted_index; i < _shelf_size - 8; ++i) {
        if (_shelf_tab[i] != color) {
            ++i;
            counter = 1;
            while (_shelf_tab[i] != color) {
                ++counter;
                ++i;
            }
            if (counter % 4 == 1) {
                _move_other_from_end(color, i++);
                _move_other_from_end(color, i++);
                _move_other_from_end(color, i);// it's not incremented due to for loop increment
            } else if (counter % 4 == 2) {
                _move_other_from_end(color, i++);
                _move_other_from_end(color, i);
            } else if (counter % 4 == 3) {
                _move_other_from_end(color, i);
            }
        }
    }
    // move different colors (grouped in previous phases) to the end
    for (int k = 0, i = _first_unsorted_index; k < different_color_unsorted_elem / 4; ++k) {
        while (_shelf_tab[i] == color)
            ++i;
        if (i > _shelf_size - 4)
            break;
        _move(i);
    }

    counter = 0;
    for (int i = _shelf_size - 4; i < _shelf_size; ++i) {
        if (_shelf_tab[i] == color)
            ++counter;
    }

    for (int i = _first_unsorted_index - 2; i < _first_unsorted_index + 2; ++i) {
        if (_shelf_tab[i] == color)
            ++counter;
    }

    _first_unsorted_index += this->_counter[color] - counter - n;

    for (int i = 0; i < counter; ++i) {
        _move_from_end(color, _first_unsorted_index++);
    }
    //move 1-3 unsorted elements that were treated as proper elements to have multiple of 4 different color elements
    // note that _first_unsorted_index is fixed here so it points to the proper element
    if (n != 0) {
        _move(tmp);
        _first_unsorted_index -= 4;

        for (int i = 0; i < different_color_unsorted_elem / 4; ++i) {
            _move(_first_unsorted_index);
        }
        _first_unsorted_index += n;
    }
}


int SpaceSort::_find_other_color_pos(const int color) const {
    int i = _first_unsorted_index;
    while (i < _shelf_size && _shelf_tab[i++] == color);
    return --i;
}


void SpaceSort::_move_from_end(const int color, const int pos) {
    for (int i = _shelf_size - 1; i >= pos; --i) {
        if (_shelf_tab[i] == color) {
            _move_to_beg(i, pos);
            break;
        }
    }
}

void SpaceSort::_move_other_from_end(const int color, const int pos) {
    for (int i = _shelf_size - 1; i >= pos; --i) {
        if (_shelf_tab[i] != color) {
            _move_to_beg(i, pos);
            break;
        }
    }
}