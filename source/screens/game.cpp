#include "./screens.hpp"
#include "./game_class.hpp"
#include "../states.hpp"
#include "../grachi.hpp"
#include "../atrc_fd.hpp"

game running_game;

void game::add_to_console(console_item ci){

    this->console_items.push_back(ci);
}

void game::initialize(){
    console_item ci = console_item(text_wrapping(sf::Vector2i(0,0), sf::Vector2i(CONSOLE_WIDTH, 50), utf8_decode("Hello"), gbw_preset, p), sec);
    this->add_to_console(ci);
}

void game::load(){

}

void game::draw_console_screen(){

}

void game::draw_game(){
    game::draw_console_screen();
}
void game::draw_esc_overlay(){}

void game::events(){
    sf::Event event;
    while (window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void game_master_loop(){
    switch(game_state){
        case game_states::initialize: 
            running_game = game();
            running_game.events();
            running_game.initialize();
            game_state = game_states::in_game;
            break;
        case game_states::load_game:
            running_game = game();
            running_game.events();
            running_game.load();
            game_state = game_states::in_game;
            break;
        case game_states::in_game: 
            running_game.events();
            clear_window();
            running_game.draw_game();
            update_window();
            break;
        case game_states::in_options: 
            break;
        case game_states::in_esc_menu: 
            break;
    }        
}

