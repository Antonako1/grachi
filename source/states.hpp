#ifndef STATES_H
#define STATES_H

extern int main_state;
extern int main_menu_state;
extern int game_state;

enum main_states{
    ms_in_main_menu,
    ms_in_game,
};

enum main_menu_states {
    ms_initialize,
    mms_in_main_menu,
    mms_in_options,
    mms_start_new_game,
    mms_load_game,
};

enum game_states{
    gs_initialize,
    gs_in_game,
    gs_in_esc_menu,
    gs_in_options
};

#endif // STATES_H