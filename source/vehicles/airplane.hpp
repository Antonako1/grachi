#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <memory>
#include <vector>
#include <string>

class Airplane_Armament{
public:
private:

};

enum pylon_carry_types{
    pct_AH = 0, // AH    = Air to Air Heat seeking missile
    pct_AR, // AR    = Air to Air Radar seeking missile
    pct_AA, // AA    = Air to Air Active radar seeking missile
    pct_LB, // LB    = Laser-quided Bomb
    pct_TB, // TB    = TV-quided Bomb
    pct_B,  // B     = Unquided Bomb
    pct_CB, // CB    = Cluster bomb
    pct_LR, // LR    = Laser-quided rocket
    pct_TV, // TV    = TV-quided rocket
    pct_R,  // R     = Unquided rocket
    pct_F,  // F     = Fuel tank
    pct_C,  // C     = COUNTERMEASURE_POD
    pct_G,  // G     = GUN_POD
    pct_amount,
};

class Pylon{
public:
    void initialize_pylon(ATRCFiledata *fd, size_t pylon_number);
private:
    Airplane_Armament contents;
    std::vector<size_t> _carry_types;
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
enum airplane_states{
    as_crew_idle,
    as_crew_moving_to_airplane,
    as_at_rearming,
    as_at_refueling,
    as_at_repairing,
    as_starting_up_engines,
    as_at_changing_pilot,
    as_at_taxiing,
    as_at_awaiting_takeoff,
    as_at_taking_off,
    as_en_route,
    as_air_to_air_combat,
    as_air_to_ground_combat,
    as_at_job_finished,
};

enum airplane_evade_states{
    aes_evade_manpad,
    aes_evade_air_to_air_radar_missile,
    aes_evade_air_to_air_heatseeking_missile,
    aes_evade_air_to_air_unknown_missile,
    aes_evage_ground_fire,
    aes_evade_radar_ping,
    aes_evade_radar_lock,
};

enum airplane_air_to_ground_combat_states{
    aagcs_firing_rocket,
    aagcs_firing_main_gun,
    aagcs_firing_gun_pod,
    aagcs_dropping_bomb,
    aagcs_dropping_t_bomb,
    aagcs_dropping_l_bomb,
};

enum airplane_types{
    at_cas = 0,
    at_fgh,
    at_bmb,
    at_awa,
    at_het,
    at_hea,
    at_crg,
    at_ash,
    at_ewa,
    at_amount,
};

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
        size_t _type;
        size_t _pylon_amount;
        std::vector<Pylon> _pylons;
        size_t _fuel;
        double _fuel_consumption;

        size_t state;
        size_t next_state;
        std::vector<size_t> state_queue;
};


#endif //AIRPLANE_H