#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

enum class pylon_carry_types{
    AH = 0, // AH    = Air to Air Heat seeking missile
    AR,     // AR    = Air to Air Radar seeking missile
    AA,     // AA    = Air to Air Active radar seeking missile
    LB,     // LB    = Laser-quided Bomb
    TB,     // TB    = TV-quided Bomb
    B,      // B     = Unquided Bomb
    CB,     // CB    = Cluster bomb
    LR,     // LR    = Laser-quided rocket
    TR,     // TR    = TV-quided rocket
    R,      // R     = Unquided rocket
    F,      // F     = Fuel tank
    C,      // C     = COUNTERMEASURE_POD
    G,      // G     = GUN_POD
    amount,
};



enum class armament_general_type{
    AIR_TO_AIR,
    AIR_TO_GROUND,
    FUEL_TANK,
    COUNTERMEASURE_POD,
    GUN_POD,
};

class Airplane_Armament{
public:
    // Takes in the name of the armament.
    // Will automatically add the path to it and file extension
    void initialize_armament(std::string &armament_name);
private:
    pylon_carry_types type; // takes in pylon_carry_type
    armament_general_type general_type;
};



class Pylon{
public:
    void initialize_pylon(ATRCFiledata *fd, size_t pylon_number);
private:
    Airplane_Armament contents;
    std::vector<pylon_carry_types> _carry_types;
};

/*+++
idle
moving to airplane
re-arm refuel
start up
taxii
await take off
take off
en route
---*/
enum class airplane_states{
    crew_idle,
    crew_moving_to_airplane,
    at_rearming,
    at_refueling,
    at_repairing,
    starting_up_engines,
    at_changing_pilot,
    at_taxiing,
    at_awaiting_takeoff,
    at_taking_off,
    en_route,
    air_to_air_combat,
    air_to_ground_combat,
    at_job_finished,
};

enum class airplane_evade_states{
    evade_manpad,
    evade_air_to_air_radar_missile,
    evade_air_to_air_heatseeking_missile,
    evade_air_to_air_unknown_missile,
    evage_ground_fire,
    evade_radar_ping,
    evade_radar_lock,
};

enum class airplane_air_to_ground_combat_states{
    firing_rocket,
    firing_main_gun,
    firing_gun_pod,
    dropping_bomb,
    dropping_t_bomb,
    dropping_l_bomb,
};


enum class airplane_types{
    cas = 0,
    fgh,
    bmb,
    awa,
    het,
    hea,
    crg,
    ash,
    ewa,
    amount,
};
#define SIZE_MAX_AIRPLANE_TYPES (airplane_types)SIZE_MAX

class Airplane{
public:
    // Takes in the name of the airplane.
    // Will automatically add the path to it and file extension
    void initialize_airplane(const std::string& airplane_name);
    // Returns all the pylons
    const std::vector<Pylon>& get_pylons() const;

    // Returns a specific pylon. Returns empty armament
    const Pylon& get_pylon(size_t pylon_position) const;

private:
        std::string _name;
        std::string _name_2locale;
        airplane_types _type;
        size_t _pylon_amount;
        std::vector<Pylon> _pylons;
        size_t _fuel;
        double _fuel_consumption;

        size_t state;
        size_t next_state;
        std::vector<size_t> state_queue;
};


#endif //AIRPLANE_H