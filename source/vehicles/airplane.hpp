#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <memory>
#include <vector>
#include <string>

class Airplane_Armament{

};

class Airplane{
public:
    // Returns all the pylons
    std::vector<Airplane_Armament>* get_pylons();

    // Returns a specific pylon. Will throw exception if out of range
    Airplane_Armament* get_pylon(int pylon_position);
private:
        int _pylon_amount;
        std::vector<Airplane_Armament> _pylons;
};


#endif //AIRPLANE_H