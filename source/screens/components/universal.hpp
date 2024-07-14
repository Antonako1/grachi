#pragma once
#include <SFML/Graphics.hpp>
#include "./button.hpp"

// returns true if clips out of bounds
bool check_text_clipping(const sf::Text& text_block, const sf::RectangleShape& rect);

// std::tuple<left, right>
std::tuple<float, float> get_lr_overflow(const sf::Text& text_block, const sf::RectangleShape& rect);

#define TEXT_SCROLL_SPEED 0.5

extern float last_text_rotate;

class button;
void rotating_text_button(button &instance);