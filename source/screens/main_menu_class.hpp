#ifndef MAIN_MENU_CLASS_H
#define MAIN_MENU_CLASS_H

#include "./screens.hpp"
#include "../hardware.hpp"

class Main_Menu{
public:
    void initialize();
    void events();
    void draw_main_menu();
    void draw_option_overlay();
private:
    mouse s_mouse ;
    keyboard s_keyboard;
};

#endif //MAIN_MENU_CLASS_H