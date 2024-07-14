#include "./button.hpp"

button::button
( 
    size_t x, 
    size_t y,
    sf::Rect<float> rect,
    colour_preset colours,
    std::string txt,
    style_element stl
)
    : x(x), y(y), rect(rect), colours(colours), text(txt), style(stl)
{
    this->text_block = sf::Text(this->text, font, this->style.size);
    construct_draw_rectangle();
    this->text_block.setPosition(this->draw_rectangle.getPosition());
}

#include "../../msg.hpp"
void button::draw(mouse ms){
    if(this->hover_on(ms.pos)){
        this->draw_rectangle.setFillColor(this->colours.background);
        this->draw_rectangle.setOutlineColor(this->colours.border);
        this->text_block.setFillColor(this->colours.text);
    } else {
        this->draw_rectangle.setFillColor(this->colours.opposite_background);
        this->draw_rectangle.setOutlineColor(this->colours.opposite_border);
        this->text_block.setFillColor(this->colours.opposite_text);
    }
    window.draw(this->draw_rectangle);
    window.draw(this->text_block);
}
bool button::hover_on(sf::Vector2i ms){
    bool res = this->rect.contains((sf::Vector2f)ms);
    return !res;
}

void button::construct_draw_rectangle(){
    draw_rectangle.setSize(sf::Vector2f(rect.width, rect.height));
    draw_rectangle.setPosition(sf::Vector2f(rect.left, rect.top));
}