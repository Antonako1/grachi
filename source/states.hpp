#ifndef STATES_H
#define STATES_H

extern int main_state;
extern int main_menu_state;
extern int game_state;

enum class main_states{
    in_main_menu,
    in_game,
};

enum class main_menu_states {
    initialize,
    in_main_menu,
    in_options,
    start_new_game,
    load_game,
};

enum class game_states{
    initialize,
    in_game,
    in_esc_menu,
    in_options
};

#endif // STATES_H