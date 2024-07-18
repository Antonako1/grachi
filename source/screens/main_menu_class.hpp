#ifndef MAIN_MENU_CLASS_H
#define MAIN_MENU_CLASS_H
#include <vector>
#include <sfml/Graphics.hpp>
#include "./components/button.hpp"
#include "./components/text.hpp"
#include "./screens.hpp"
#include "../hardware.hpp"

class button;
class text;

enum class MAIN_MENU_BUTTONS{
    Start,
    Continue,
    Load,
    Gallery,
    Logs,
    Options,
    Exit,
};

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
    std::vector<text> texts;
    sf::Texture background_image;
    sf::Sprite background_image_sprite;
};

#endif //MAIN_MENU_CLASS_H