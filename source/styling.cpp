#include "./styling.hpp"
#define UNIVERSAL_BORDER_WIDTH      2

style_element h1(64, UNIVERSAL_BORDER_WIDTH);
style_element h2(48, UNIVERSAL_BORDER_WIDTH);
style_element h3(36, UNIVERSAL_BORDER_WIDTH);
style_element p (24, UNIVERSAL_BORDER_WIDTH);
_colours colours;

colour_preset gbw_preset(
    colours.green,
    colours.black,
    colours.white,
    sf::Color(200, 200, 200, 255),
    colours.black,
    sf::Color(0, 255, 102, 255)
);
colour_preset ggw_preset(
    colours.green,
    colours.gray,
    colours.white,
    sf::Color(200, 200, 200, 255),
    colours.black,
    sf::Color(0, 255, 102, 255)
);