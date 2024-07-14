#ifndef MAIN_MENU_CLASS_H
#define MAIN_MENU_CLASS_H
#include <vector>
#include "./components/button.hpp"
#include "./screens.hpp"
#include "../hardware.hpp"

class button;

class Main_Menu{
public:
    void initialize();
    void events();
    void draw_main_menu();
    void draw_option_overlay();
private:
    std::vector<button> buttons;
    mouse ms;
    keyboard kb;
};

#endif //MAIN_MENU_CLASS_H