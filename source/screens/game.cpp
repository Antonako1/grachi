#include "./screens.hpp"
#include "./game_class.hpp"
#include "../states.hpp"
#include "../grachi.hpp"

game running_game;

void game::initialize(){

}

void game::load(){

}

void game::draw_game(){}
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

