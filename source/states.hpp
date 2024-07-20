#ifndef STATES_H
#define STATES_H

enum class main_states{
    in_main_menu,
    in_game,
};

enum class main_menu_states {
    initialize,
    in_main_menu,
    in_options,
};

enum class game_states{
    initialize,
    load_game,
    in_game,
    in_esc_menu,
    in_options
};

extern main_states main_state;
extern main_menu_states main_menu_state;
extern game_states game_state;


#endif // STATES_H