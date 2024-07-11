#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <ATRC.h>

#include "./airplane.hpp"
#include "../msg.hpp"
#include "../grachi.hpp"
#include "../atrc_fd.hpp"
std::string airplane_quick_read(ATRCFiledata* fd, const std::string &key){
    return read_key_as_string(fd, "VEHICLE", key);
}

std::string pylon_carry_types[] = {
    "AH",   std::to_string(pct_AH),
    "AR",   std::to_string(pct_AR),
    "AA",   std::to_string(pct_AA),
    "LB",   std::to_string(pct_LB),
    "TB",   std::to_string(pct_TB),
    "B",    std::to_string(pct_B),
    "CB",   std::to_string(pct_CB),
    "LR",   std::to_string(pct_LR),
    "TV",   std::to_string(pct_TV),
    "R",    std::to_string(pct_R),
    "F",    std::to_string(pct_F),
    "C",    std::to_string(pct_C),
    "G",    std::to_string(pct_G),
};

std::vector<size_t> pylon_carry_types_to_size_t(const std::vector<std::string> &pylon_contents){
    std::vector<size_t> res;
    for(const std::string &content : pylon_contents){
        for(size_t i = 0; i < sizeof(pylon_carry_types) / sizeof(pylon_carry_types[0]); i+=2){
            if(content == pylon_carry_types[i]){
                res.push_back(str_to_size_t(pylon_carry_types[i+1]));
            }
        }
    }
    return res;
};


void Pylon::initialize_pylon(ATRCFiledata *fd, size_t pylon_number){
    m_dbg("Initializing pylon");
    std::string predefine_contents = "pylon_" + std::to_string(pylon_number); // will hold data later
    std::string pylon_name = predefine_contents + "_contents";
    std::vector<std::string> pylon_contents = atrc_value_to_list(airplane_quick_read(fd, pylon_name));
    
    this->_carry_types = pylon_carry_types_to_size_t(pylon_contents);

    for(auto lol : this->_carry_types){
        m_dbg(std::to_string(lol));
    }
}



std::string airplane_types[] = {
    "cas", std::to_string(at_cas),
    "fgh", std::to_string(at_fgh),
    "bmb", std::to_string(at_bmb),
    "awa", std::to_string(at_awa),
    "het", std::to_string(at_het),
    "hea", std::to_string(at_hea),
    "crg", std::to_string(at_crg),
    "ash", std::to_string(at_ash),
    "ewa", std::to_string(at_ewa),
};

size_t airplane_type_to_enum(const std::string &type){
    for(size_t i = 0; i < sizeof(airplane_types) / sizeof(airplane_types[0]); i+=2){
        if(airplane_types[i] == type){
            return str_to_size_t(airplane_types[i+1]);
        }
    }
    return SIZE_MAX;
}
#include <iostream>
void Airplane::initialize_airplane(const std::string& airplane_name){
    const std::string atrc_file_path = "vehicles\\planes\\" + airplane_name + ".atrc";
    
    std::unique_ptr<ATRCFiledata> fd = reader(atrc_file_path);
    this->_type = airplane_type_to_enum(airplane_quick_read(fd.get(), "type"));
    if(this->_type == SIZE_MAX){
        m_nrm("Invalid airplane type in file " + atrc_file_path, DATA_VALUE_ERROR, FL_AIRPLANE, true);
        return;
    }
    m_dbg("Type: " + std::to_string(this->_type));
    this->_name = airplane_quick_read(fd.get(), "name");
    this->_name_2locale = airplane_quick_read(fd.get(), "name_2locale");
    m_dbg("Names: " + this->_name + " and " + this->_name_2locale);

    this->_pylon_amount = str_to_size_t(airplane_quick_read(fd.get(), "pylon_amount"));
    if(this->_pylon_amount == std::string::npos){
        this->_pylon_amount = 0;
    }
    
    // pylon amount starts counting from 1
    for(size_t i = 1; i < this->_pylon_amount + 1; i++){
        Pylon _pylon;
        _pylon.initialize_pylon(fd.get(), i);
    }
    m_dbg("\nPylon info start");
    m_dbg("Pylon amounts: " + std::to_string(this->_pylon_amount));
}

const std::vector<Pylon>& Airplane::get_pylons() const {
    return this->_pylons;
}

const Pylon& Airplane::get_pylon(size_t pylon_position) const {
    m_dbg("Pylon request " + std::to_string(pylon_position) + "/" + std::to_string(this->_pylons.size()));
    if (pylon_position >= _pylon_amount || pylon_position < 0) {
        throw std::out_of_range("Invalid pylon position"); // TODO MAKE BETTER
    }
    return this->_pylons.at(pylon_position);
}

