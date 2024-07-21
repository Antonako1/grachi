#pragma once
#include "../../styling.hpp"
#include <sfml/Graphics/Rect.hpp>
#include <string>
#include "../screens.hpp"
#include "./universal.hpp"

class text{
public:
    text(
        sf::Vector2i pos,
        sf::Vector2i size,
        std::wstring txt,
        colour_preset colours,
        style_element style
    );
    size_t abs_overflow = 0; // ROTATING TEXT
    size_t rotating_text_pointer = 0;  // ROTATING TEXT
    std::wstring str_text;
    void draw();
    sf::Text text_block;
private:
    style_element style;
    colour_preset colours;
    sf::RectangleShape rect;
    bool text_overflow_works();
    size_t temp_pointer; // ROTATING TEXT
    void initialize();
    bool is_text_clipping = false; // ROTATING TEXT
};


class text_wrapping{
public:
    text_wrapping(
        sf::Vector2i pos,
        sf::Vector2i size,
        std::wstring txt,
        colour_preset colours,
        style_element style
    );
    void update_size(const sf::Vector2i new_size);  // Updates rect
    void update_pos(const sf::Vector2i new_pos);    // Updates rect
    sf::Vector2i get_size() const;
    sf::Vector2i get_pos() const;
    std::wstring str_text;
    void draw();
    sf::Text text_block;
private:
    style_element style;
    colour_preset colours;
    sf::RectangleShape rect;
    bool text_overflow_works();
    size_t temp_pointer; // WRAP
    void initialize();
    bool render_done = false; // WRAP
};