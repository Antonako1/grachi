#pragma once
#include "../../styling.hpp"
#include "../../hardware.hpp"
#include <sfml/Graphics/Rect.hpp>
#include <string>
#include "../screens.hpp"
#include <sfml/Window/Mouse.hpp>
#include "./universal.hpp"

class button{
public:
    button( 
        int x, 
        int y,
        colour_preset colours,
        std::string txt,
        style_element style
        );
    void draw(mouse ms);
    bool hover_on(sf::Vector2i ms);
    void construct_draw_rectangle();
    std::string text;
    style_element style;
    sf::Text text_block;
    size_t abs_overflow = 0;
    size_t rotating_text_pointer = 0;
private:
    int x;
    int y;
    sf::Rect<int> rect;
    colour_preset colours;
    sf::RectangleShape draw_rectangle;
    int min_width = 300;
    int min_height = 100;
    bool is_text_clipping = false;

    bool button_overflow_works();
    size_t temp_pointer;
};