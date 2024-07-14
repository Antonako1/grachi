#include "./universal.hpp"
#include "../../styling.hpp"
#include "../../grachi.hpp"
#include "../../msg.hpp"

bool check_text_clipping(const sf::Text& text_block, const sf::RectangleShape& rect) {
    // Get global bounds of the text block and the rectangle
    sf::FloatRect textBounds = text_block.getGlobalBounds();
    sf::FloatRect rectBounds = rect.getGlobalBounds();

    // Check if the text extends beyond the rectangle
    bool extendsLeft = textBounds.left < rectBounds.left;
    bool extendsRight = textBounds.left + textBounds.width > rectBounds.left + rectBounds.width;
    bool extendsTop = textBounds.top < rectBounds.top;
    bool extendsBottom = textBounds.top + textBounds.height > rectBounds.top + rectBounds.height;

    // If any condition is true, the text extends beyond the rectangle
    if (extendsLeft || extendsRight || extendsTop || extendsBottom) {
        return true;
    } else {
        return false;
    }
}

std::tuple<float, float> get_lr_overflow(const sf::Text& text_block, const sf::RectangleShape& rect){
    sf::FloatRect textBounds = text_block.getGlobalBounds();
    sf::FloatRect rectBounds = rect.getGlobalBounds();
    float extendsLeft = textBounds.left - rectBounds.left;
    bool extendsRight = (textBounds.left + textBounds.width) - (rectBounds.left + rectBounds.width);
    return std::make_tuple(extendsLeft, extendsRight);
}

enum class UNIVERSAL_TYPE{
    button = 0,
};


#ifdef DEBUG
# include <iostream>
#endif

std::string rotating_text( 
    const std::string &source_text, 
    const size_t overflow,
    size_t &pointer
    )
{
    std::string res = "";
    size_t source_length = source_text.size();
    size_t complete_length = (source_length - overflow);

    if (complete_length <= 0) {
        return res;
    }
    for(size_t i = pointer; i < complete_length + pointer && source_length > i; i++){
        res += source_text[i];
    }
    if(res.size() >= complete_length){
        pointer++;
        return res;
    }
    res += " ";
    for(size_t i = 0; res.size() < complete_length; i++){
        res += source_text[i];
    }
    pointer++;
    if(pointer > source_length){
        pointer = 0;
    }
    return res;
}

float last_text_rotate = 0;


void rotating_text_button(button &instance){
    if(sec.asSeconds() - TEXT_SCROLL_SPEED >= last_text_rotate){
        std::string res = rotating_text(instance.text, instance.abs_overflow, instance.rotating_text_pointer);
        instance.text_block.setString(res);
        last_text_rotate = sec.asSeconds();
    }
}