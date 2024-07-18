#include "./universal.hpp"
#include "../../styling.hpp"
#include "../../grachi.hpp"
#include "../../msg.hpp"
#include "../screens.hpp"


void scale_factor_calc(){
    SCALE_WIDTH = float(WINDOW_RESOLUTION_HEIGHT) / float(ORIGINAL_WINDOW_RESOLUTION_HEIGHT);
    SCALE_HEIGHT = float(WINDOW_RESOLUTION_HEIGHT) / float(ORIGINAL_WINDOW_RESOLUTION_HEIGHT);
}

sf::Vector2i scale_factor_calc_gui_element(const sf::Vector2i in){
    sf::Vector2i res;
    res.x = int((float)in.x * SCALE_WIDTH);
    res.y = int((float)in.y * SCALE_HEIGHT);
    return res;
}

#define EXTRA_CLIP_HELP 2.f
bool check_text_clipping(const sf::Text& text_block, const sf::RectangleShape& rect) {
    // Get global bounds of the text block and the rectangle
    sf::FloatRect textBounds = text_block.getGlobalBounds();
    sf::FloatRect rectBounds = rect.getGlobalBounds();

    // Check if the text extends beyond the rectangle
    bool extendsLeft = textBounds.left < rectBounds.left + EXTRA_CLIP_HELP;
    bool extendsRight = textBounds.left + textBounds.width + EXTRA_CLIP_HELP> rectBounds.left + rectBounds.width;
    bool extendsTop = textBounds.top < rectBounds.top + EXTRA_CLIP_HELP;
    bool extendsBottom = textBounds.top + textBounds.height + EXTRA_CLIP_HELP > rectBounds.top + rectBounds.height;

    // If any condition is true, the text extends beyond the rectangle
    if (extendsLeft || extendsRight
    // || extendsTop || extendsBottom
    ) {
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

// Everything rotates at the same time
float last_text_rotate = 0;

bool check_legal_rotation(){
    return sec.asSeconds() - TEXT_SCROLL_SPEED >= last_text_rotate;
}

void rotating_text_button(button &instance){
    if(check_legal_rotation()){
        std::string res = rotating_text(instance.text, instance.abs_overflow, instance.rotating_text_pointer);
        instance.text_block.setString(res);
    }
}

void rotating_text_text(text &instance){
    if(check_legal_rotation()){
        std::string res = rotating_text(instance.str_text, instance.abs_overflow, instance.rotating_text_pointer);
        instance.text_block.setString(res);
    }
}

void update_rotate_timer(){
    last_text_rotate = sec.asSeconds();
}