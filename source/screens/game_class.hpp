#pragma once
#include <sfml/Graphics.hpp>
#include <sfml/Audio.hpp>
#include "./components/text.hpp"
#include "./screens.hpp"
// #define CONSOLE_ITEM_DESPAWN_AFTER

#define CONSOLE_WIDTH (WINDOW_RESOLUTION_WIDTH - WINDOW_WIDTH_MIDDLE) + (WINDOW_WIDTH_MIDDLE / 2)

class text_wrapping;

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
    void draw_radar();

    void update_logic_ground_vehicles();
    void update_logic_airplanes();
    void update_logic_ships();
    void update_logic_infantry();
    void update_logic();

    struct console_item {
        text_wrapping txt_item;
        sf::Time time_added;
        console_item(
            text_wrapping txt,
            sf::Time ta
        ) : 
            txt_item(txt),
            time_added(ta) 
            {}
    };
    void add_to_console(console_item ci);
    void draw_console_screen();
private:
    inner_states inner_state;
    std::vector<inner_states> inner_state_queue;
    struct sradar {
        
    } radar;
    std::vector<console_item> console_items;
};