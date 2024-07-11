#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <ATRC.h>
#include <unordered_map>
#include "./airplane.hpp"
#include "../msg.hpp"
#include "../grachi.hpp"
#include "../atrc_fd.hpp"

std::string airplane_quick_read(ATRCFiledata* fd, const std::string &key){
    return read_key_as_string(fd, "VEHICLE", key);
}




const std::unordered_map<armament_general_types, std::string> armament_general_types_to_string = {
    {armament_general_types::AIR_TO_AIR, "AIR_TO_AIR"},
    {armament_general_types::AIR_TO_GROUND, "AIR_TO_GROUND"},
    {armament_general_types::FUEL_TANK, "FUEL_TANK"},
    {armament_general_types::COUNTERMEASURE_POD, "COUNTERMEASURE_POD"},
    {armament_general_types::GUN_POD, "GUN_POD"},
};

void Airplane_Armament::initialize_armament(std::string &armament_name){
    m_dbg("Initializing armament of type: '" + armament_name + "'!");
    std::unique_ptr<ATRCFiledata> fd = reader("\\vehicles\\planes\\armament\\"+armament_name+".atrc");
    //for(const auto &[key, value] : armament_general_types_to_string){
    //}

    this->state = armament_states::idle;
}

// TODO
/*
std::tuple<double, double> calculate_range_and_hours_remaining_current_fuel_load(const size_t fuel, const size_t combined_thrust){
    double range, hours;
    double jet_fuel_density_kg_l = 800;

    return std::tie(range,hours);
}
*/

const std::unordered_map<pylon_carry_types, std::string> pylon_carry_types_to_string = {
    { pylon_carry_types::AH, "AH" },
    { pylon_carry_types::AR, "AR" },
    { pylon_carry_types::AA, "AA" },
    { pylon_carry_types::LB, "LB" },
    { pylon_carry_types::TB, "TB" },
    { pylon_carry_types::B, "B" },
    { pylon_carry_types::CB, "CB" },
    { pylon_carry_types::LR, "LR" },
    { pylon_carry_types::TR, "TR" },
    { pylon_carry_types::R, "R" },
    { pylon_carry_types::F, "F" },
    { pylon_carry_types::C, "C" },
    { pylon_carry_types::G, "G" }
};

std::vector<pylon_carry_types> pylon_carry_types_to_size_t(const std::vector<std::string> &pylon_contents){
    std::vector<pylon_carry_types> res;
    for(const std::string &content : pylon_contents){
        for(const auto &[key, value] : pylon_carry_types_to_string){
            if(value == content){
                res.push_back(key);
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
    if(pylon_contents.size() == 0){
        // TODO: in production, turn to fatal error
        #ifdef DEBUG
        m_nrm("Pylon content key does not have a value defined. File: " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, false);
        #else
        m_nrm("Pylon content key does not have a value defined. File: " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
        #endif
        return;
    }
    
    this->_carry_types = pylon_carry_types_to_size_t(pylon_contents);

    predefine_contents = airplane_quick_read(fd, predefine_contents);
    if(predefine_contents != ""){
        Airplane_Armament aa;
        aa.initialize_armament(predefine_contents);
        this->state = aircraft_pylon_state::loaded;
    } else {
        this->state = aircraft_pylon_state::empty;
    }
}



const std::unordered_map<airplane_types, std::string> airplane_types_to_string = {
    { airplane_types::cas, "cas" },
    { airplane_types::fgh, "fgh" },
    { airplane_types::bmb, "bmb" },
    { airplane_types::awa, "awa" },
    { airplane_types::het, "het" },
    { airplane_types::hea, "hea" },
    { airplane_types::crg, "crg" },
    { airplane_types::ash, "ash" },
    { airplane_types::ewa, "ewa" },
};


#include <iostream>
airplane_types airplane_type_to_enum(const std::string &type){
    for(const auto &[key, value] : airplane_types_to_string){
        if(value == type){
            return key;
        }
    }
    return SIZE_MAX_AIRPLANE_TYPES;
}
#include <iostream>
void Airplane::initialize_airplane(const std::string& airplane_name){
    m_dbg("Initializing airplane!");
    const std::string atrc_file_path = "vehicles\\planes\\" + airplane_name + ".atrc";
    
    std::unique_ptr<ATRCFiledata> fd = reader(atrc_file_path);
    this->_type = airplane_type_to_enum(airplane_quick_read(fd.get(), "type"));
    if(this->_type == SIZE_MAX_AIRPLANE_TYPES){
        m_nrm("Invalid airplane type in file " + atrc_file_path, DATA_VALUE_ERROR, FL_AIRPLANE, true);
        return;
    }
    m_dbg("Type: " + std::to_string((size_t)this->_type));
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
        m_nrm("Can't get pylon request: "+ std::to_string(pylon_position) + "/" + std::to_string(this->_pylons.size()), LIST_OUT_OF_BOUNDS_ERROR, FL_AIRPLANE, true);
        return;
    }
    return this->_pylons.at(pylon_position);
}

