#pragma once
#include "../../styling.hpp"
#include "../../hardware.hpp"
#include <sfml/Graphics/Rect.hpp>
#include <string>
#include "../screens.hpp"
#include <sfml/Window/Mouse.hpp>
#include "./universal.hpp"

#define BUTTON_NORMAL_WIDTH         200
#define BUTTON_NORMAL_HEIGHT        50
#define BUTTON_NORMAL_HEIGHT_ADDITION   10
#define BUTTON_NORMAL_HEIGHT_ADD    (BUTTON_NORMAL_HEIGHT + BUTTON_NORMAL_HEIGHT_ADDITION)
class button{
public:
    button( 
        sf::Vector2i coord,
        sf::Vector2i size,
        colour_preset colours,
        std::string txt,
        style_element style,
        size_t act
        );
    button( 
        sf::Vector2i coord,
        colour_preset colours,
        std::string txt,
        style_element style,
        size_t act
        );
    void draw(mouse ms);
    bool hover_on(const sf::Vector2i ms) const;
    std::string text;
    style_element style;
    sf::Text text_block;
    size_t abs_overflow = 0; // ROTATING TEXT
    size_t rotating_text_pointer = 0;  // ROTATING TEXT
    size_t action;          
private:
    void construct_draw_rectangle(); // ONE TIME USE ON INITIALIZATION!!!!
    void initialize();
    sf::Vector2i coordinates;
    sf::Vector2i size;
    sf::Rect<int> rect;
    colour_preset colours;
    sf::RectangleShape draw_rectangle;
    bool is_text_clipping = false; // ROTATING TEXT

    bool button_overflow_works();
    size_t temp_pointer; // ROTATING TEXT
};