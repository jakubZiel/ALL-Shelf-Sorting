#include "input_generator.h"
#include <random>


InputGenerator::InputGenerator(unsigned int length) : _length(length), _gen(_rd()), _dis(0.0, 1.0){}
/**
 * Generate vector of colors where the probability that next is the same is equal p.
 * @param p probability that the next color will be the same as current.
 */
void InputGenerator::gen_same_next(float p) {
    // generate first instance
    unsigned current_instance = _choose_first_instance();
    _colors_vector.push_back(current_instance);
    for (unsigned i = 1; i < _length; i++) {
        double random_number = _dis(_gen);
        if (random_number < p) {
            _colors_vector.push_back(current_instance);
        } else {
            current_instance = _choose_next_instance(current_instance);
            _colors_vector.push_back(current_instance);
        }
    }
}
unsigned InputGenerator::_choose_first_instance(){
    double p = _dis(_gen);
    if (p < 0.25){
        return 0;
    }
    else if (p < 0.5){
        return 1;
    }
    else if (p< 0.75){
        return 2;
    }
    else{
        return 3;
    }

}

unsigned int InputGenerator::_choose_next_instance(unsigned int current_instance) {
    double random_number = _dis(_gen);
    if (random_number < 0.33){
        return (current_instance + 1)%N;
    }
    else if(random_number < 0.66){
        return (current_instance + 2)%N;
    }
    else{
        return (current_instance + 3)%N;
    }
}

std::vector<unsigned> &InputGenerator::get_color_vector() {
    return _colors_vector;
}
