#include <memory>
#include <vector>
#include <string>
#include "./airplane.hpp"
#include <stdexcept>


std::vector<Airplane_Armament>* Airplane::get_pylons(){
    return &this->_pylons;
}

Airplane_Armament* Airplane::get_pylon(int pylon_position) {
    if (pylon_position >= _pylon_amount || pylon_position < 0) {
        throw std::out_of_range("Invalid pylon position");
    }
    return &this->_pylons.at(pylon_position);
}

