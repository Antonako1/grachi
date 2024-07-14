#pragma once
#include "../../styling.hpp"
#include "../../hardware.hpp"
#include <sfml/Graphics/Rect.hpp>
#include <string>
#include "../screens.hpp"
#include <sfml/Window/Mouse.hpp>

class button{
public:
    button( 
        size_t x, 
        size_t y,
        sf::Rect<float> rect,
        colour_preset colours,
        std::string txt,
        style_element style
        );
    void draw(mouse ms);
    bool hover_on(sf::Vector2i ms);
    void construct_draw_rectangle();
private:
    size_t x;
    size_t y;
    sf::Rect<float> rect;
    colour_preset colours;
    std::string text;
    sf::Text text_block;
    sf::RectangleShape draw_rectangle;
    style_element style;
};