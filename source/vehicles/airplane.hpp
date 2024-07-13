#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <memory>
#include <vector>
#include <string>

class Voice_Warning_System{};

enum class armament_general_types{
    AIR_TO_AIR,
    AIR_TO_GROUND,
    FUEL_TANK,
    COUNTERMEASURE_POD,
    GUN_POD,
    TARGETING_POD,
};

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
    TP,     // TP    = Targeting pod
    amount,
};



enum class armament_general_type{
    AIR_TO_AIR,
    AIR_TO_GROUND,
    FUEL_TANK,
    COUNTERMEASURE_POD,
    GUN_POD,
};

enum class armament_states{
    in_use,
    idle,
    destroyed,
    non_operational,
};

class Airplane_Armament{
public:
    // Takes in the name of the armament.
    // Will automatically add the path to it and file extension
    void initialize_armament(std::string &armament_name);
private:
    pylon_carry_types type;
    armament_general_types general_type;
    std::string name;
    std::string name_2locale;
    armament_states state;
};


enum class aircraft_pylon_state{
    loaded,
    armament_in_use,
    empty,
    non_operational,
};

class Pylon{
public:
    void initialize_pylon(ATRCFiledata *fd, size_t pylon_number);
private:
    Airplane_Armament contents;
    std::vector<pylon_carry_types> _carry_types;
    aircraft_pylon_state state;
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


enum class airplane_combat_states{
    firing_ah_missile,
    firing_ar_missile,
    firing_aa_missile,
    firing_main_gun,
    firing_gun_pod,
    dropping_bomb,
    dropping_t_bomb,
    dropping_l_bomb,
    dropping_cluster_bomb,
    firing_rocket,
    firing_t_rocket,
    firing_l_rocket,
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

class Airplane_Radar_IRST{
public:
    bool is_radar;                  // in km
    bool is_radar_pulse_doplar;     // only for radar
    size_t equipment_range;         // in km. On IRST it is sensitivity from 0-100
    size_t min_azimuth_scan;        // in km
    size_t max_azimuth_scan;        // in km
    size_t min_elevation_scan;      // in km
    size_t max_elevation_scan;      // in km
    size_t radar_full_sweep_in;     // in seconds
    bool radar_has_tws;             // only for radar
    bool boresight_mode;
    bool vertical_scan_mode;
// private:
};

enum class airplane_part_states{
    operational,
    turned_off,
    broken,
};

enum class airplane_part_positions{
    // General
    left,
    right,
    middle,
    front,
    back,
    whole_fuselage,
    left_wing,
    right_wing,

    // only for engines
    // first from left
    engine_wing_left_1,
    // second from left
    engine_wing_left_2,
    // first from right
    engine_wing_right_1,
    // second from right
    engine_wing_right_2,
};

enum class airplane_parts{
    wing,
    // fuselage,
    // Fuselage chopped down into three sections
    fuselage_front,
    fuselage_middle,
    fuselage_back,
    vertical_stabilizer,
    horizontal_stabilizer,
    rudder,
    airbrake,
    engine,
    flap,
    ballistic_computer_bombs,
    ballistic_computer_rockets,
    ballistic_computer_gun,
    fuel_tank,
    aileron,
    slat,
    cockpit,
    navigation_system,
    communication_system,
    nose_cone,
    landing_gear,
    radar,
    ecm,
    ircm,
    hydraulics,
    electricity,
    fuel_pump,
    laser_pod,
    drag_chute,
    tv_pod,
};

enum class rwr_level{
    no_rwr = 0, // 0 = Does not have an rwr
    only_front, // 1 = Only shows in front
    only_back, // 2 = Only shows in back
    sps_10, // 3 = Shows in four equal areas around the airplane (sps-10)
    sps_10_upgrade, // 4 = Same but can differentiate locks and radar pings
    sps_15, // 5 = Same as sps-15 in mig-29s, su-25s
    all_direction, // 6 = Shows in all directions equally
};

#define AIRPLANE_PART_MAX_DURABILITY 200
class Airplane_Part{
public:
    void initialize_part(airplane_parts part, airplane_part_positions pos);
private:
    // Part conditions on a range from 0 to set constant
    size_t durability;
    airplane_part_states state;
    airplane_parts part;
    airplane_part_positions position;
};

class Airplane{
public:
    // Takes in the name of the airplane.
    // Will automatically add the path to it and file extension
    void initialize_airplane(const std::string& airplane_name);
    // Returns all the pylons
    const std::vector<Pylon>& get_pylons() const;

    // Returns a specific pylon. check out of bounds before calling
    const Pylon& get_pylon( const size_t pylon_position) const;

    size_t get_throttle() const;
    // Updates thrust automatically
    void set_throttle(const size_t throttle_percent);
    size_t get_main_gun_ammo_count() const;
    size_t get_thrust() const;
    void   set_main_gun_ammo_count(const size_t new_value);
    
    size_t get_speed() const;
    void set_speed(const size_t new_value);
    size_t get_empty_weight() const;
    size_t get_max_takeoff_weight() const;
    size_t get_fuel_amount() const;

    // Both engines
    double get_fuel_consumption() const;

    // Sets for all engines
    void set_fuel_consumption(const double new_value);
    
    // Returns all engine value
    double get_fuel_consumption_rate() const;
private:
        std::string _name;
        std::string _name_2locale;
        airplane_types _type;
        size_t _pylon_amount;
        std::vector<Pylon> _pylons;


        Airplane_Armament main_gun;
        size_t main_gun_ammo_count;

        airplane_states state;
        airplane_states next_state;
        std::vector<airplane_states> state_queue;

        // current thrust in kgf
        size_t thrust;
        // current throttle in percents
        size_t throttle;
        // current speed in kmh
        size_t speed;
        // constant empty weight in kg
        size_t empty_weight;
        // constant max weight in kg
        size_t max_takeoff_weight;
        // airplane's current weight in kg
        size_t current_weight;
        // current fuel amount in liters
        size_t fuel;
        // max fuel quantity
        size_t max_fuel;
        // current fuel consumption in kg/kgf/h
        double fuel_consumption;
        // How much fuel engine consumes in kg/h
        double fuel_consumption_rate;
        // constant set temperature in celsius
        size_t engine_temperature;

        size_t working_engines;

        size_t built_in_countermeasure_count;

        // TODO Remove, only needed for initializing
        size_t engine_amount;
        size_t single_engine_max_thrust;

        std::vector<Airplane_Part> parts;

        bool ircm = false;
        bool ecm = false;
        bool laser_pod = false;
        bool tv_pod = false;
        bool engine_fire_extinguishers = false;
        bool are_fuel_tank_sealable = false;
        bool are_flaps_fixed = false;
        bool drag_chute = false;
        bool ejection_seat = false;

        rwr_level airplane_rwr_level;

        // in kmh
        size_t drag_chute_min_deployment_speed; 


        
        bool hmd = false;
        // Radar
        bool does_have_radar = false;
        Airplane_Radar_IRST radar;
        // IRST
        bool does_have_irst = false;
        Airplane_Radar_IRST irst;

        size_t radar_cross_section; // in m^2
};

// NOTE: thrust has to be up to date upon calling
std::tuple<double, double> calculate_range_and_hours_remaining_with_current_fuel_load(Airplane &instance);

#endif //AIRPLANE_H