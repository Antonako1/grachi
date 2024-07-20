#pragma once
#include <SFML/Graphics.hpp>
#include "./button.hpp"

// returns true if clips out of bounds
bool check_text_clipping(const sf::Text& text_block, const sf::RectangleShape& rect);

// std::tuple<left, right>
std::tuple<float, float> get_lr_overflow(const sf::Text& text_block, const sf::RectangleShape& rect);

#define TEXT_SCROLL_SPEED   0.5

extern float last_text_rotate;

class button;
void rotating_text_button(button &instance);

class text;
void rotating_text_text(text &instance);

void update_rotate_timer();
bool check_legal_rotation();

enum class ARGUI {
    WIDTH,
    HEIGHT,
};

sf::Vector2i scale_factor_calc_gui_element(const sf::Vector2i in);

void scale_factor_calc();

#define LEFT_TO_RIGHT_TEXT_RENDER_SPEED 0.02