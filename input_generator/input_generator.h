#ifndef SHELF_SORTING_INPUT_GENERATOR_H
#define SHELF_SORTING_INPUT_GENERATOR_H
#include <vector>
#include <random>

class InputGenerator {
private :
    const unsigned N = 4; // number of different color types
    const unsigned _length;
    std::vector<unsigned> _colors_vector;
    // random
    std::random_device _rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 _gen; //Standard mersenne_twister_engine seeded with _rd()
    std::uniform_real_distribution<> _dis;

    unsigned int _choose_next_instance(unsigned int current_instance);
    unsigned _choose_first_instance();

public:
    InputGenerator(unsigned length);
    void gen_same_next(float p);
    std::vector<unsigned> &get_color_vector();

};
#endif //SHELF_SORTING_INPUT_GENERATOR_H
