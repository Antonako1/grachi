#ifndef SCREENS_H
#define SCREENS_H
#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
#include "./main_menu_class.hpp"
#include "./game_class.hpp"
#include "../hardware.hpp"

extern Main_Menu main_menu;
extern game running_game;

extern sf::RenderWindow window;
extern sf::Font font;

extern size_t ORIGINAL_WINDOW_RESOLUTION_HEIGHT;
extern size_t ORIGINAL_WINDOW_RESOLUTION_HEIGHT;
extern size_t WINDOW_RESOLUTION_WIDTH;
extern size_t WINDOW_RESOLUTION_HEIGHT;
extern size_t WINDOW_ASPECT_RATIO_WIDTH;
extern size_t WINDOW_ASPECT_RATIO_HEIGHT;
extern size_t WINDOW_WIDTH_MIDDLE;
extern size_t WINDOW_HEIGHT_MIDDLE;


extern float SCALE_WIDTH;
extern float SCALE_HEIGHT;

void main_menu_main_loop();

void game_master_loop();

void update_window();
void clear_window();

#endif // SCREENS_H