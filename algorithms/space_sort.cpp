#include "space_sort.h"

void SpaceSort::sort() {
    for (int i = 0; i < 3; i++) {
        if (_counter[i] > 6) {
            _make_spaces(i);
        }
        else {
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
    int l = (int) (_shelf_size - _first_unsorted_index - this->_counter[color]);
    int n = 0;
    int tmp = _first_unsorted_index;

    if (l % 4 == 1) {
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        n += 3;
        l -= 1;
    } else if (l % 4 == 2) {
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        n += 2;
        l -= 2;
    } else if (l % 4 == 3) {
        _move_to_beg(_find_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        _move_to_beg(_find_other_color_pos(color), _first_unsorted_index++);
        n += 1;
        l -= 3;
    }

    int counter;
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
                _move_other_from_end(color, i);
            } else if (counter % 4 == 2) {
                _move_other_from_end(color, i++);
                _move_other_from_end(color, i);
            } else if (counter % 4 == 3) {
                _move_other_from_end(color, i);
            }
        }
    }

    for (int k = 0, i = _first_unsorted_index; k < l / 4; ++k) {
        while (_shelf_tab[i] == color)
            ++i;
        if (i > _shelf_size - 4)
            break;
        _move(i);
    }

    counter = 0;
    for (int i = (int) (_shelf_size - 4); i < _shelf_size; ++i) {
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

    if (n != 0) {
        _move(tmp);
        _first_unsorted_index -= 4;

        for (int i = 0; i < l / 4; ++i) {
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

void SpaceSort::_move_other_to_end(const int color, const int pos) {
    for (int i = (int) (_shelf_size - 1); i >= pos; --i) {
        if (_shelf_tab[i] != color) {
            _move_to_beg(i, pos);
            break;
        }
    }
}
void SpaceSort::_move_from_end(const int color, const int pos) {
    for (int i = (int) (_shelf_size - 1); i >= pos; --i) {
        if (_shelf_tab[i] == color) {
            _move_to_beg(i, pos);
            break;
        }
    }
}

void SpaceSort::_move_other_from_end(const int color, const int pos) {
    for (int i = (int) (_shelf_size - 1); i >= pos; --i) {
        if (_shelf_tab[i] != color) {
            _move_to_beg(i, pos);
            break;
        }
    }
}