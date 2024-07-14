#include "./screens.hpp"
#include "../states.hpp"
#include "../msg.hpp"
#include "../atrc_fd.hpp"
#include "./main_menu_class.hpp"

Main_Menu main_menu;



void Main_Menu::initialize(){
    // Start
    std::unique_ptr<ATRCFiledata> fd = reader("locale\\main_menu.atrc");
    std::string buffer = read_key_as_string(fd.get(), "MAIN_MENU", "start_button"); 
    button temp_button(100, 100, gbw_preset, buffer, h3);
    this->buttons.push_back(temp_button);
    // Continue
    // Load
    // Gallery
    // Logs
    // Options
    // Exit to windows
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
            case sf::Event::MouseMoved:
                this->ms.pos.x = event.mouseMove.x;
                this->ms.pos.y = event.mouseMove.y;
                break;
        }
    }
}

void Main_Menu::draw_main_menu(){
    window.clear();
    for(auto &btn : this->buttons){
        btn.draw(this->ms);
    }
    window.display();
}

void Main_Menu::draw_option_overlay(){
    window.clear();
    window.display();
}


void main_menu_main_loop(){
    switch(main_menu_state){
        case main_menu_states::initialize: 
            main_menu = Main_Menu();
            m_nrm("Initializing main menu", PROGRAM_INFO, FL_MAIN_MENU, false);
            main_menu.initialize();
            main_menu_state = main_menu_states::in_main_menu;
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