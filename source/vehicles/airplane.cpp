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
    {armament_general_types::TARGETING_POD, "TARGETING_POD"},
};

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
    { pylon_carry_types::G, "G" },
    { pylon_carry_types::TP, "TP" },
};

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

bool isnpos(const size_t &val){
    if(val==std::string::npos){
        return true;
    }
    return false;
}

airplane_types airplane_type_to_enum(const std::string &type){
    for(const auto &[key, value] : airplane_types_to_string){
        if(value == type){
            return key;
        }
    }
    return SIZE_MAX_AIRPLANE_TYPES;
}

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




void Airplane_Part::initialize_part(airplane_parts part, airplane_part_positions pos){
    this->part = part;
    this->position = pos;
    this->durability = AIRPLANE_PART_MAX_DURABILITY;
    this->state = airplane_part_states::turned_off;
}





void Airplane_Armament::initialize_armament(std::string &armament_name){
    m_dbg("Initializing armament of type: '" + armament_name + "'!");
    std::unique_ptr<ATRCFiledata> fd = reader("\\vehicles\\planes\\armament\\"+armament_name+".atrc");
    //for(const auto &[key, value] : armament_general_types_to_string){
    //}

    this->state = armament_states::idle;
}






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












void Airplane::initialize_airplane(const std::string& airplane_name){
    m_dbg("Initializing airplane!");
    const std::string atrc_file_path = "vehicles\\planes\\" + airplane_name + ".atrc";
    
    std::unique_ptr<ATRCFiledata> fd = reader(atrc_file_path);
    this->_type = airplane_type_to_enum(airplane_quick_read(fd.get(), "type"));
    if(this->_type == SIZE_MAX_AIRPLANE_TYPES){
        m_nrm("Invalid airplane type in file " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
        return;
    }
    m_dbg("Type: " + std::to_string((size_t)this->_type));
    this->_name = airplane_quick_read(fd.get(), "name");
    this->_name_2locale = airplane_quick_read(fd.get(), "name_2locale");
    m_dbg("Names: " + this->_name + " and " + this->_name_2locale);

    this->_pylon_amount = str_to_size_t(airplane_quick_read(fd.get(), "pylon_amount"));
    if(isnpos(this->_pylon_amount)){
        this->_pylon_amount = 0;
    }
    // pylon amount starts counting from 1
    for(size_t i = 1; i < this->_pylon_amount + 1; i++){
        Pylon _pylon;
        _pylon.initialize_pylon(fd.get(), i);
    }
    m_dbg("Pylon amounts: " + std::to_string(this->_pylon_amount));

    Airplane_Armament main_gun; 
    main_gun.initialize_armament(airplane_quick_read(fd.get(), "main_gun"));
    this->main_gun = main_gun;
    this->main_gun_ammo_count = str_to_size_t(airplane_quick_read(fd.get(), "main_gun_ammo_count"));
    if(isnpos(this->main_gun_ammo_count)){
        m_nrm("Invalid main gun ammo count in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE , true);
    }

    this->empty_weight = str_to_size_t(airplane_quick_read(fd.get(), "empty_weight"));
    if(isnpos(this->empty_weight)){
        m_nrm("Invalid empty weight in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    this->max_takeoff_weight = str_to_size_t(airplane_quick_read(fd.get(), "max_takeoff_weight"));
    if(isnpos(this->max_takeoff_weight)){
        m_nrm("Invalid max takeoff weight in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    this->max_fuel = str_to_size_t(airplane_quick_read(fd.get(), "fuel"));
    if(isnpos(this->max_fuel)){
        m_nrm("Invalid fuel amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }
    this->fuel = this->max_fuel;
    this->fuel_consumption_rate = str_to_double(airplane_quick_read(fd.get(), "fuel_consumption_rate"));
    if(this->fuel_consumption_rate <= 0){
        m_nrm("Invalid fuel_consumption_rate in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    this->engine_amount = str_to_size_t(airplane_quick_read(fd.get(), "engines"));
    if(isnpos(this->fuel)){
        m_nrm("Invalid engine amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    if(this->engine_amount != 1 && this->engine_amount != 2 && this->engine_amount != 4){
        m_nrm("Invalid engine amount (put 1, 2, 4) in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    this->engine_temperature = str_to_size_t(airplane_quick_read(fd.get(), "engine_temperature"));
    if(isnpos(this->engine_temperature)){
        m_nrm("Invalid engine temperature amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    this->built_in_countermeasure_count = str_to_size_t(airplane_quick_read(fd.get(), "built_in_countermeasure_count"));
    if(isnpos(this->built_in_countermeasure_count)){
        m_nrm("Invalid built_in_countermeasure_count amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    this->single_engine_max_thrust = str_to_size_t(airplane_quick_read(fd.get(), "max_thrust"));
    if(isnpos(this->single_engine_max_thrust)){
        m_nrm("Invalid single_engine_max_thrust amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }
    size_t rudder_vertical_stabilizers = str_to_size_t(airplane_quick_read(fd.get(), "rudders_and_v_stabilizer_amount"));
    if(isnpos(rudder_vertical_stabilizers) || rudder_vertical_stabilizers != 1 && rudder_vertical_stabilizers != 2){
        m_nrm("Invalid rudders_and_v_stabilizer_amount amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    size_t internal_fuel_tank = str_to_size_t(airplane_quick_read(fd.get(), "amount_of_inner_fuel_tanks"));
    if(isnpos(internal_fuel_tank)){
        m_nrm("Invalid amount_of_inner_fuel_tanks amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    this->set_speed(0);
    this->set_fuel_consumption(0);
    this->set_throttle(0);
    m_dbg("empty weight: "+std::to_string(this->empty_weight));
    m_dbg("max takeoff weight: "+std::to_string(this->max_takeoff_weight));
    m_dbg("fuel: "+std::to_string(this->fuel));
    m_dbg("thrust: "+std::to_string(this->thrust));
    m_dbg("engine temperature: "+std::to_string(this->engine_temperature));
    m_dbg("built_in_countermeasure_count: "+std::to_string(this->built_in_countermeasure_count));
    m_dbg("engine_amount: "+std::to_string(this->engine_amount));
    m_dbg("single_engine_max_thrust: "+std::to_string(this->single_engine_max_thrust));
    m_dbg("fuel_consumption: "+std::to_string(this->fuel_consumption));
    m_dbg("rudder_vertical_stabilizers: "+std::to_string(rudder_vertical_stabilizers));
    m_dbg("amount_of_inner_fuel_tanks: "+std::to_string(internal_fuel_tank));

    // Initializes all the aircraft parts
    this->working_engines = this->engine_amount;
    if(this->engine_amount == 1){
        Airplane_Part engine;
        engine.initialize_part(airplane_parts::engine, airplane_part_positions::back);
        this->parts.push_back(engine);
    }
    else if(this->engine_amount == 2){
        for(size_t i = 0; i < this->working_engines;i++){
            Airplane_Part engine;
            if(i==0){
                engine.initialize_part(airplane_parts::engine, airplane_part_positions::left);
            } else {
                engine.initialize_part(airplane_parts::engine, airplane_part_positions::right);
            }
            this->parts.push_back(engine);
        }
    } else {
        for(size_t i = 0; i < this->working_engines;i++){
            Airplane_Part engine;
            if(i==0){
                engine.initialize_part(airplane_parts::engine, airplane_part_positions::engine_wing_left_1);
            } 
            else if (i==1){
                engine.initialize_part(airplane_parts::engine, airplane_part_positions::engine_wing_left_2);
            }
            else if (i==2){
                engine.initialize_part(airplane_parts::engine, airplane_part_positions::engine_wing_right_1);
            }
            else {
                engine.initialize_part(airplane_parts::engine, airplane_part_positions::engine_wing_right_2);
            }
            this->parts.push_back(engine);
        }
    }

    // wings
    Airplane_Part part;
    part.initialize_part(airplane_parts::wing, airplane_part_positions::left);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::wing, airplane_part_positions::right);
    this->parts.push_back(part);
    // fuselage
    part.initialize_part(airplane_parts::fuselage_front, airplane_part_positions::front);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::fuselage_middle, airplane_part_positions::middle);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::fuselage_back, airplane_part_positions::back);
    this->parts.push_back(part);
    // Stabilizers
    if(rudder_vertical_stabilizers == 1){
        part.initialize_part(airplane_parts::vertical_stabilizer, airplane_part_positions::middle);
        this->parts.push_back(part);
        part.initialize_part(airplane_parts::rudder, airplane_part_positions::middle);
        this->parts.push_back(part);
    } else {
        part.initialize_part(airplane_parts::vertical_stabilizer, airplane_part_positions::left);
        this->parts.push_back(part);
        part.initialize_part(airplane_parts::vertical_stabilizer, airplane_part_positions::right);
        this->parts.push_back(part);
        part.initialize_part(airplane_parts::rudder, airplane_part_positions::left);
        this->parts.push_back(part);
        part.initialize_part(airplane_parts::rudder, airplane_part_positions::right);
        this->parts.push_back(part);
    }

    part.initialize_part(airplane_parts::horizontal_stabilizer, airplane_part_positions::left);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::horizontal_stabilizer, airplane_part_positions::right);
    this->parts.push_back(part);

    if(str_to_bool(airplane_quick_read(fd.get(), "airbrakes"))){
        part.initialize_part(airplane_parts::airbrake, airplane_part_positions::middle);
        this->parts.push_back(part);
    }

    if(str_to_bool(airplane_quick_read(fd.get(), "are_flaps_fixed"))){
        this->are_flaps_fixed = true;
    }

    part.initialize_part(airplane_parts::flap, airplane_part_positions::left);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::flap, airplane_part_positions::right);
    this->parts.push_back(part);

    if(str_to_bool(airplane_quick_read(fd.get(), "ballistics_computer_guns"))){
        part.initialize_part(airplane_parts::ballistic_computer_gun, airplane_part_positions::front);
        this->parts.push_back(part);
    }
    if(str_to_bool(airplane_quick_read(fd.get(), "ballistics_computer_rockets"))){
        part.initialize_part(airplane_parts::ballistic_computer_rockets, airplane_part_positions::front);
        this->parts.push_back(part);
    }
    if(str_to_bool(airplane_quick_read(fd.get(), "ballistics_computer_bombs"))){
        part.initialize_part(airplane_parts::ballistic_computer_bombs, airplane_part_positions::front);
        this->parts.push_back(part);
    }

    if(str_to_bool(airplane_quick_read(fd.get(), "engine_fire_extinguishers"))){
        this->engine_fire_extinguishers;
    }
    if(str_to_bool(airplane_quick_read(fd.get(), "are_fuel_tank_sealable"))){
        this->are_fuel_tank_sealable = true;
    }

    for(size_t i = 0 ; i < internal_fuel_tank; i++){
        part.initialize_part(airplane_parts::fuel_tank, airplane_part_positions::whole_fuselage);
        this->parts.push_back(part);
        part.initialize_part(airplane_parts::fuel_pump, airplane_part_positions::whole_fuselage);
        this->parts.push_back(part);
    }

    part.initialize_part(airplane_parts::aileron, airplane_part_positions::left);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::aileron, airplane_part_positions::right);
    this->parts.push_back(part);

    part.initialize_part(airplane_parts::slat, airplane_part_positions::left);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::slat, airplane_part_positions::right);
    this->parts.push_back(part);

    part.initialize_part(airplane_parts::cockpit, airplane_part_positions::front);
    this->parts.push_back(part);
    
    part.initialize_part(airplane_parts::radar, airplane_part_positions::front);
    this->parts.push_back(part);

    if(str_to_bool(airplane_quick_read(fd.get(), "built_in_ecm"))){
        this->ecm = true;
        part.initialize_part(airplane_parts::ecm, airplane_part_positions::back);
        this->parts.push_back(part);
    }
    if(str_to_bool(airplane_quick_read(fd.get(), "built_in_ircm"))){
        this->ircm = true;
        part.initialize_part(airplane_parts::ircm, airplane_part_positions::back);
        this->parts.push_back(part);
    }


    if(str_to_bool(airplane_quick_read(fd.get(), "built_in_tv_pod"))){
        this->tv_pod = true;
        part.initialize_part(airplane_parts::tv_pod, airplane_part_positions::front);
        this->parts.push_back(part);
    }
    if(str_to_bool(airplane_quick_read(fd.get(), "built_in_laser_pod"))){
        this->laser_pod = true;
        part.initialize_part(airplane_parts::laser_pod, airplane_part_positions::front);
        this->parts.push_back(part);
    }
    if(str_to_bool(airplane_quick_read(fd.get(), "ejection_seat"))){
        this->ejection_seat = true;
    }
    

    if(str_to_bool(airplane_quick_read(fd.get(), "drag_chute"))){
        part.initialize_part(airplane_parts::drag_chute, airplane_part_positions::back);
        this->parts.push_back(part);
        this->drag_chute_min_deployment_speed = str_to_size_t(airplane_quick_read(fd.get(), "drag_chute_min_deployment_speed"));
        if(isnpos(this->drag_chute_min_deployment_speed)){
            m_nrm("Invalid drag_chute_min_deployment_speed amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
        }
    }
    size_t temporary_rwr_lvl = str_to_size_t(airplane_quick_read(fd.get(), "rwr"));
    if(isnpos(temporary_rwr_lvl)){
        m_nrm("Invalid rwr amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }
    try{
        this->airplane_rwr_level = static_cast<rwr_level>(temporary_rwr_lvl);
    } catch(...){
        m_nrm("Invalid rwr amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    
    part.initialize_part(airplane_parts::navigation_system, airplane_part_positions::front);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::communication_system, airplane_part_positions::front);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::nose_cone, airplane_part_positions::front);
    this->parts.push_back(part);

    part.initialize_part(airplane_parts::landing_gear, airplane_part_positions::front);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::landing_gear, airplane_part_positions::left);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::landing_gear, airplane_part_positions::right);
    this->parts.push_back(part);

    part.initialize_part(airplane_parts::hydraulics, airplane_part_positions::front);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::hydraulics, airplane_part_positions::back);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::hydraulics, airplane_part_positions::left);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::hydraulics, airplane_part_positions::right);
    this->parts.push_back(part);

    part.initialize_part(airplane_parts::electricity, airplane_part_positions::front);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::electricity, airplane_part_positions::back);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::electricity, airplane_part_positions::left);
    this->parts.push_back(part);
    part.initialize_part(airplane_parts::electricity, airplane_part_positions::right);
    this->parts.push_back(part);



    // TODO BOTH
    // radar
    if(str_to_bool(airplane_quick_read(fd.get(), "does_have_radar"))){
        this->does_have_radar = true;
        if(str_to_bool(airplane_quick_read(fd.get(), "helmet_mounted_display"))){
            this->hmd = true;
        }
        Airplane_Radar_IRST temp_radar;
        temp_radar.is_radar = true;
        this->radar = temp_radar;
    }
    // irst
    if(str_to_bool(airplane_quick_read(fd.get(), "does_have_irst"))){
        this->does_have_irst = true;
        if(str_to_bool(airplane_quick_read(fd.get(), "helmet_mounted_display"))){
            this->hmd = true;
        }
        Airplane_Radar_IRST temp_irst;
        temp_irst.is_radar = false;
        this->irst = temp_irst;
    }




    this->radar_cross_section = str_to_size_t(airplane_quick_read(fd.get(), "radar_cross_section"));
    if(isnpos(this->radar_cross_section)){
        m_nrm("Invalid radar_cross_section amount in " + fd->Filename, DATA_VALUE_ERROR, FL_AIRPLANE, true);
    }

    // m_dbg("Calculating flight range and remaining time");
    // this->set_throttle(100);
    // this->set_speed(750);
    // m_dbg("Throttle: " + std::to_string(this->get_throttle()) + "%");
    // m_dbg("Speed: " + std::to_string(this->get_speed()) + "kmh");
    // std::tuple<double, double> results = calculate_range_and_hours_remaining_with_current_fuel_load(*this);
    // double range = std::get<0>(results);
    // double hours = std::get<1>(results);
    // m_dbg("Hours of flight time: " + std::to_string(hours));
    // m_dbg("Flight range (km): " + std::to_string(range));


}

const std::vector<Pylon>& Airplane::get_pylons() const {
    return this->_pylons;
}


const Pylon& Airplane::get_pylon(size_t pylon_position) const {
    m_dbg("Pylon request " + std::to_string(pylon_position) + "/" + std::to_string(this->_pylons.size()));
    if (pylon_position >= _pylon_amount || pylon_position < 0) {
        m_nrm("Can't get pylon request: "+ std::to_string(pylon_position) + "/" + std::to_string(this->_pylons.size()), LIST_OUT_OF_BOUNDS_ERROR, FL_AIRPLANE, true);
    }
    return this->_pylons.at(pylon_position);
}

// !!REWORKS WITH PARTS MADE!!

#include <iostream>
// TODO REWORK
void update_fuel_consumption(Airplane &instance){
    // const double kgf = 9.80665;
    // size_t thrust = instance.get_thrust();

    // const double f = thrust * kgf;
    // const double m = instance.get_fuel_consumption_rate();
    // double tsfc = m / f + 1; 
    // m_dbg(std::to_string(tsfc));
    // m_dbg(std::to_string(m));
    // m_dbg(std::to_string(f));
    // m_dbg(std::to_string(thrust));
    // instance.set_fuel_consumption(tsfc);
}




std::tuple<double, double> calculate_range_and_hours_remaining_with_current_fuel_load(Airplane &instance){
    // double jet_fuel_density_kg_l = 0.8;
    // size_t thrust = instance.get_thrust();
    // double fuel_consumption = instance.get_fuel_consumption(); // Cannot be zero
    // size_t current_fuel_amount = instance.get_fuel_amount();

    double hours = 0;
    double range = 0;
    // if(thrust == 0 || current_fuel_amount == 0) {
    //     return std::make_tuple(range,hours);
    // }

    // double fuel_consumption_rate = thrust * fuel_consumption; 
    // double fuel_quantity_kg = current_fuel_amount * jet_fuel_density_kg_l;

    // if (fuel_consumption_rate > 0) {
    //     hours = fuel_quantity_kg / fuel_consumption_rate;
    //     range = hours * instance.get_speed();
    // }

    return std::make_tuple(range, hours);
}



void Airplane::set_throttle(const size_t throttle_percent){
    this->throttle = throttle_percent;
    /*+++
    throttle   | x
    100 | this.max.t
    ---*/
    // TODO DO THINGS HERE: size_t working_amount_of_engines;
    this->thrust = ((this->throttle * this->single_engine_max_thrust) / 100) * this->engine_amount;
    update_fuel_consumption(*this);
}

size_t Airplane::get_speed() const{
    return this->speed;
};
void Airplane::set_speed(const size_t new_value){
    this->speed = new_value;
};
size_t Airplane::get_empty_weight() const{
    return this->empty_weight;
};

size_t Airplane::get_max_takeoff_weight() const{
    return this->max_takeoff_weight;
};

double Airplane::get_fuel_consumption() const{
    return this->fuel_consumption;
};

size_t Airplane::get_fuel_amount() const{
    // TODO add external fuel tanks
    return this->fuel;
}


// TODO REWORK x2
double Airplane::get_fuel_consumption_rate() const{
    return this->fuel_consumption_rate;
}
size_t Airplane::get_main_gun_ammo_count() const{
    return this->main_gun_ammo_count;
};

// TODO REWORK x2
void Airplane::set_fuel_consumption(const double new_value){
    this->fuel_consumption = new_value; // TODO ENGINE AMOUNT
}
void Airplane::set_main_gun_ammo_count(size_t new_value){
    this->main_gun_ammo_count = new_value;
};


size_t Airplane::get_thrust()const{
    return this->thrust;
};
size_t Airplane::get_throttle()const{
    return this->throttle;
};