#include "./screens.hpp"
#include "../states.hpp"
#include "../grachi.hpp"
#include "../msg.hpp"
#include "../atrc_fd.hpp"
#include "./main_menu_class.hpp"
#include "./components/universal.hpp" // rescale

Main_Menu main_menu;

void Main_Menu::initialize(){
    std::unique_ptr<ATRCFiledata> fd = reader("locale\\main_menu.atrc");
    // Start
    std::string buffer = read_key_as_string(fd.get(), "MAIN_MENU", "start_button"); 
    int y = 400;
    size_t x = WINDOW_RESOLUTION_WIDTH - BUTTON_NORMAL_WIDTH - (BUTTON_NORMAL_WIDTH/2);
    button temp_button = button(sf::Vector2i(x, y), gbw_preset, buffer, h3, static_cast<size_t>(MAIN_MENU_BUTTONS::Start));
    this->buttons.push_back(temp_button);
    y += BUTTON_NORMAL_HEIGHT_ADD;
    // Continue
    buffer = read_key_as_string(fd.get(), "MAIN_MENU", "continue_button"); 
    temp_button = button(sf::Vector2i(x, y), gbw_preset, buffer, h3, static_cast<size_t>(MAIN_MENU_BUTTONS::Continue));
    this->buttons.push_back(temp_button);
    y += BUTTON_NORMAL_HEIGHT_ADD;
    // Load
    buffer = read_key_as_string(fd.get(), "MAIN_MENU", "load_button"); 
    temp_button = button(sf::Vector2i(x, y), gbw_preset, buffer, h3, static_cast<size_t>(MAIN_MENU_BUTTONS::Load));
    this->buttons.push_back(temp_button);
    y += BUTTON_NORMAL_HEIGHT_ADD;
    // Gallery
    buffer = read_key_as_string(fd.get(), "MAIN_MENU", "gallery_button"); 
    temp_button = button(sf::Vector2i(x, y), gbw_preset, buffer, h3, static_cast<size_t>(MAIN_MENU_BUTTONS::Gallery));
    this->buttons.push_back(temp_button);
    y += BUTTON_NORMAL_HEIGHT_ADD;
    // Logs
    buffer = read_key_as_string(fd.get(), "MAIN_MENU", "logs_button"); 
    temp_button = button(sf::Vector2i(x, y), gbw_preset, buffer, h3, static_cast<size_t>(MAIN_MENU_BUTTONS::Logs));
    this->buttons.push_back(temp_button);
    y += BUTTON_NORMAL_HEIGHT_ADD;
    // Options
    buffer = read_key_as_string(fd.get(), "MAIN_MENU", "options_button"); 
    temp_button = button(sf::Vector2i(x, y), gbw_preset, buffer, h3, static_cast<size_t>(MAIN_MENU_BUTTONS::Options));
    this->buttons.push_back(temp_button);
    y += BUTTON_NORMAL_HEIGHT_ADD;
    // Exit to windows
    buffer = read_key_as_string(fd.get(), "MAIN_MENU", "exit_button"); 
    temp_button = button(sf::Vector2i(x, y), gbw_preset, buffer, h3, static_cast<size_t>(MAIN_MENU_BUTTONS::Exit));
    this->buttons.push_back(temp_button);
    y += BUTTON_NORMAL_HEIGHT_ADD;


    // Heading text
    buffer = read_key_as_string(fd.get(), "MAIN_MENU", "heading_text");
    text temp_text = text(sf::Vector2i(x-50, 100), sf::Vector2i(BUTTON_NORMAL_WIDTH + (50*2), 100), utf8_decode(buffer), gbw_preset, h1);
    this->texts.push_back(temp_text);

    if(!this->background_image.loadFromFile(image_path + "non_map\\menu_background.bmp")){
        m_nrm("Error loading main menu image '"+image_path+"non_map\\menu_background.bmp"+"'", IMAGE_ERROR, FL_MAIN_MENU, true);
    }
    this->background_image_sprite.setTexture(this->background_image);
    sf::Vector2u window_size = window.getSize();
    sf::Vector2u texture_size = this->background_image.getSize();

    // Calculate the scale factors to fit the texture to the window
    float scale_x = static_cast<float>(window_size.x) / texture_size.x;
    float scale_y = static_cast<float>(window_size.y) / texture_size.y;

    // Set the position and scale
    this->background_image_sprite.setPosition(0, 0);
    this->background_image_sprite.setScale(scale_x, scale_y);
}

void Main_Menu::events(){
    sf::Event event;
    while (window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
            // case sf::Event::MouseButtonReleased:
                for(const button &btn : this->buttons){
                    if(btn.hover_on(this->ms.pos)){
                        switch(static_cast<MAIN_MENU_BUTTONS>(btn.action)){
                            case MAIN_MENU_BUTTONS::Start:
                                m_dbg("STARTING GAME");
                                main_state = main_states::in_game;
                                game_state = game_states::initialize;
                                break;
                            case MAIN_MENU_BUTTONS::Continue:
                                m_dbg("CONTINUING LAST GAME");
                                main_state = main_states::in_game;
                                game_state = game_states::load_game;
                                break;
                            case MAIN_MENU_BUTTONS::Load:
                                m_dbg("CHOOSE SAVE GAME GAME");
                                break;
                            case MAIN_MENU_BUTTONS::Gallery:
                            case MAIN_MENU_BUTTONS::Logs:
                            case MAIN_MENU_BUTTONS::Options:
                                break;
                            case MAIN_MENU_BUTTONS::Exit:
                                window.close();
                                break;
                            default:
                                m_nrm("Click on a undefined button... action_(" + std::to_string(btn.action) + ')', PROGRAM_INFO, FL_MAIN_MENU, false);
                                break;
                        }
                    }
                }
                break;
            case sf::Event::MouseMoved:
                this->ms.pos.x = event.mouseMove.x;
                this->ms.pos.y = event.mouseMove.y;
                this->ms.pos = sf::Vector2i(window.mapPixelToCoords(ms.pos));
                break;
        }
    }
}

void Main_Menu::draw_main_menu(){
    window.draw(this->background_image_sprite);
    for(auto &btn : this->buttons){
        btn.draw(this->ms);
    }
    for(auto &txt : this->texts){
        txt.draw();
    }
    if(check_legal_rotation()){
        update_rotate_timer();
    }
}

void Main_Menu::draw_option_overlay(){

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
            clear_window();
            main_menu.draw_main_menu();
            update_window();
            break;
        case main_menu_states::in_options: 
            main_menu.events();
            clear_window();
            main_menu.draw_option_overlay();
            update_window();
            break;
    }
};