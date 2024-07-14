#pragma once
#include <sfml/Graphics/Color.hpp>

struct style_element {
    unsigned int size;
    style_element(
        unsigned int sz
    ) : size(sz) {}
};

extern style_element h1;
extern style_element h2;
extern style_element h3;
extern style_element p;

extern struct _colours {
    sf::Color green = sf::Color(0, 255, 102, 255);

    sf::Color black = sf::Color(15, 15, 15, 255);
    
    sf::Color white = sf::Color(200, 200, 200, 255);
} colours;


struct colour_preset {
    sf::Color text;
    sf::Color background;
    sf::Color border;
    sf::Color opposite_text;
    sf::Color opposite_background;
    sf::Color opposite_border;

    colour_preset(
        sf::Color t = sf::Color(),
        sf::Color bg = sf::Color(),
        sf::Color br = sf::Color(),
        sf::Color ot = sf::Color(),
        sf::Color obg = sf::Color(),
        sf::Color obr = sf::Color()
    )
    : text(t), background(bg), border(br), opposite_text(ot), opposite_background(obg), opposite_border(obr) {}
};

/*+++
pos 0, 1, 2 = Green, black, white
opposites 3, 4, 5 = White, black, green
---*/
extern colour_preset gbw_preset;