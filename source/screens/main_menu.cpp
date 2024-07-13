#include "./screens.hpp"
#include "../states.hpp"
#include "../msg.hpp"

Main_Menu main_menu;

void Main_Menu::initialize(){

}

void Main_Menu::events(){
    sf::Event event;
    while (window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                break;
        }
    }
}

void Main_Menu::draw_main_menu(){
    window.clear();
    window.display();
}

void Main_Menu::draw_option_overlay(){
    window.clear();
    window.display();
}


void main_menu_main_loop(){
    switch(main_menu_state){
        case main_menu_states::initialize: 
            m_dbg("Initializing main menu");
            main_menu.initialize();
            main_menu_state = main_menu_states::in_main_menu;
            m_dbg("Showing main menu");
            break;
        case main_menu_states::in_main_menu: 
            main_menu.events();
            main_menu.draw_main_menu();
            break;
        case main_menu_states::in_options: 
            main_menu.events();
            main_menu.draw_option_overlay();
            break;
        case main_menu_states::start_new_game: 
            break;
        case main_menu_states::load_game: 
            break;
    }
};