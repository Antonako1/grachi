#include "./button.hpp"

#include "../../msg.hpp"
#ifdef DEBUG
# include <iostream>
#endif

bool button::button_overflow_works(){
    this->temp_pointer--;
    this->text_block.setString(this->text.substr(0, (size_t)this->temp_pointer));
    this->text_block.setOrigin(this->text_block.getGlobalBounds().getSize() / 2.f + this->text_block.getLocalBounds().getPosition());
    this->text_block.setPosition((sf::Vector2f)(this->rect.getPosition() + this->rect.getSize() / 2));
    return check_text_clipping(this->text_block, this->draw_rectangle);
}

button::button 
( 
    sf::Vector2i coord,
    colour_preset colours,
    std::string txt,
    style_element stl,
    size_t act
)
    : coordinates(coord), colours(colours), text(txt), style(stl), action(act)
{
    this->rect = sf::Rect<int>(
        this->coordinates.x, 
        this->coordinates.y, 
        BUTTON_NORMAL_WIDTH,
        BUTTON_NORMAL_HEIGHT
    );
    this->initialize();
}
button::button
( 
    sf::Vector2i coord,
    sf::Vector2i size,
    colour_preset colours,
    std::string txt,
    style_element stl,
    size_t act
)
    : coordinates(coord), size(size), colours(colours), text(txt), style(stl), action(act)
{   
    this->rect = sf::Rect<int>(
        this->coordinates.x, 
        this->coordinates.y, 
        this->size.x, 
        this->size.y
    );
    this->initialize();
}

void button::initialize(){
    this->text_block = sf::Text(this->text, font, this->style.size);

    this->text_block.setOrigin(this->text_block.getGlobalBounds().getSize() / 2.f + this->text_block.getLocalBounds().getPosition());
    this->text_block.setPosition((sf::Vector2f)(this->rect.getPosition() + this->rect.getSize() / 2));

    this->draw_rectangle.setOutlineThickness(this->style.border_thickness);
    construct_draw_rectangle();

    if(check_text_clipping(this->text_block, this->draw_rectangle)){
        this->is_text_clipping = true;
        this->temp_pointer = this->text.size();
        while(this->button_overflow_works());
        this->abs_overflow = this->text.size() - this->temp_pointer + 1;
        this->text_block.setString(this->text.substr(0, this->text.size() - this->abs_overflow));
        this->text_block.setOrigin(this->text_block.getGlobalBounds().getSize() / 2.f + this->text_block.getLocalBounds().getPosition());
        this->text_block.setPosition((sf::Vector2f)(this->rect.getPosition() + this->rect.getSize() / 2));
    }
}

void button::draw(mouse ms){
    if(!this->hover_on(ms.pos)){
        this->draw_rectangle.setFillColor(this->colours.background);
        this->draw_rectangle.setOutlineColor(this->colours.border);
        this->text_block.setFillColor(this->colours.text);
    } else {
        this->draw_rectangle.setFillColor(this->colours.opposite_background);
        this->draw_rectangle.setOutlineColor(this->colours.opposite_border);
        // this->text_block.setFillColor(this->colours.opposite_text);
    }

    if(this->is_text_clipping){
        rotating_text_button(*this);
    }

    window.draw(this->draw_rectangle);
    window.draw(this->text_block);
}
bool button::hover_on(const sf::Vector2i ms) const {
    sf::Vector2f rect_pos = this->draw_rectangle.getPosition();
    sf::Vector2f rect_size = this->draw_rectangle.getSize();
    if(rect_pos.x <= ms.x 
    && ms.x <= rect_pos.x + rect_size.x
    && rect_pos.y <= ms.y 
    && ms.y <= rect_pos.y + rect_size.y){
        return true;
    } else {
        return false;
    }
}

void button::construct_draw_rectangle(){
    draw_rectangle.setSize((sf::Vector2f)this->rect.getSize());
    draw_rectangle.setPosition((sf::Vector2f)this->rect.getPosition());
}
