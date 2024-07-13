#ifndef SCREENS_H
#define SCREENS_H
#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
#include "./main_menu_class.hpp"

extern Main_Menu main_menu;

extern sf::RenderWindow window;
extern sf::Font font;



void main_menu_main_loop();

#endif // SCREENS_H