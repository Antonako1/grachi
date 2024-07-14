#include "./styling.hpp"
style_element h1(64);
style_element h2(48);
style_element h3(36);
style_element p(24);
_colours colours;

colour_preset gbw_preset(
    colours.green,
    colours.black,
    colours.white,
    sf::Color(200, 200, 200, 255),
    colours.black,
    sf::Color(0, 255, 102, 255)
);