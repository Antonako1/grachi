#pragma once

class game{
public:
    enum inner_states {

    };
    void initialize(); // Initializes new game
    void load();       // Initializes saved game
    void draw_game();
    void draw_esc_overlay();
    void events();
    void update_logic_radar();
    void update_logic_ground_vehicles();
    void update_logic_airplanes();
    void update_logic_ships();
    void update_logic_infantry();
    void update_logic();
private:
    size_t inner_state;
};