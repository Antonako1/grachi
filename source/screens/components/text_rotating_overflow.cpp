#include "./text.hpp"

bool text::text_overflow_works(){
    this->temp_pointer--;
    this->text_block.setString(this->str_text.substr(0, (size_t)this->temp_pointer));
    this->text_block.setOrigin(this->text_block.getGlobalBounds().getSize() / 2.f + this->text_block.getLocalBounds().getPosition());
    this->text_block.setPosition((sf::Vector2f)(this->rect.getPosition() + this->rect.getSize() / 2.f));
    return check_text_clipping(this->text_block, this->rect);
}

text::text(
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

void text::initialize(){
    this->rect.setFillColor(this->colours.background);
    this->rect.setOutlineColor(this->colours.border);
    this->text_block = sf::Text(this->str_text, font, this->style.size);

    this->text_block.setOrigin(this->text_block.getGlobalBounds().getSize() / 2.f + this->text_block.getLocalBounds().getPosition());
    this->text_block.setPosition((sf::Vector2f)(this->rect.getPosition() + this->rect.getSize() / 2.f));

    this->text_block.setFillColor(this->colours.text);
    this->rect.setOutlineThickness(this->style.border_thickness);
    if(check_text_clipping(this->text_block, this->rect)){
        this->is_text_clipping = true;
        this->temp_pointer = this->str_text.size();
        while(this->text_overflow_works());
        this->abs_overflow = this->str_text.size() - this->temp_pointer + 1;
        this->text_block.setString(this->str_text.substr(0, this->str_text.size() - this->abs_overflow));
        this->text_block.setOrigin(this->text_block.getGlobalBounds().getSize() / 2.f + this->text_block.getLocalBounds().getPosition());
        this->text_block.setPosition((sf::Vector2f)(this->rect.getPosition() + this->rect.getSize() / 2.f));
    }
}
void text::draw(){
    
    if(this->is_text_clipping){
        rotating_text_text(*this);
    }
    window.draw(this->rect);
    window.draw(this->text_block);
}