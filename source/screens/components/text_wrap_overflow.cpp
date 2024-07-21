#include "./text.hpp"
#include "./universal.hpp"

sf::Vector2i text_wrapping::get_pos() const{
    return static_cast<sf::Vector2i>(this->rect.getPosition());
} 
sf::Vector2i text_wrapping::get_size() const{
    return static_cast<sf::Vector2i>(this->rect.getSize());
} 
void text_wrapping::update_size(const sf::Vector2i new_size){
    this->rect.setSize(static_cast<sf::Vector2f>(new_size));
}

void text_wrapping::update_pos(const sf::Vector2i new_pos){
    this->rect.setSize(static_cast<sf::Vector2f>(new_pos));
}

text_wrapping::text_wrapping(
    sf::Vector2i pos,
    sf::Vector2i size,
    std::wstring txt,
    colour_preset colours,
    style_element style
) 
: str_text(txt), colours(colours), style(style)
{
    this->rect.setPosition(static_cast<sf::Vector2f>(pos));
    this->rect.setSize(static_cast<sf::Vector2f>(size));
    this->initialize();
} 
void text_wrapping::initialize(){
    this->rect.setFillColor(this->colours.background);
    this->rect.setOutlineColor(this->colours.border);
    this->text_block = sf::Text(this->str_text, font, this->style.size);

    // TODO WIP CONTINUE
}

void text_wrapping::draw(){
    if(!this->render_done){
        // update render animation pointer
    }
    window.draw(this->rect);
    window.draw(this->text_block);
}