#include <iostream>
#include <windows.h>
#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <ATRC.h>
#include "./grachi.hpp"
#include "./states.hpp"
#include "./screens/screens.hpp"
#include "./screens/components/universal.hpp"
#include "./msg.hpp"
#include "./styling.hpp"
#include "./atrc_fd.hpp"

#include "./vehicles/airplane.hpp"
std::string project_root_path;
std::string project_in_home_docs;
std::string atrc_path;
std::string image_path;
std::string audio_path;

main_states main_state;
main_menu_states main_menu_state;
game_states game_state;

size_t ORIGINAL_WINDOW_RESOLUTION_WIDTH = 1024;
size_t ORIGINAL_WINDOW_RESOLUTION_HEIGHT = 768;
size_t WINDOW_WIDTH_MIDDLE = ORIGINAL_WINDOW_RESOLUTION_WIDTH / 2;
size_t WINDOW_HEIGHT_MIDDLE = ORIGINAL_WINDOW_RESOLUTION_HEIGHT / 2;
size_t WINDOW_RESOLUTION_WIDTH      = 1024;
size_t WINDOW_RESOLUTION_HEIGHT     = 768;
size_t WINDOW_ASPECT_RATIO_WIDTH    = 4;
size_t WINDOW_ASPECT_RATIO_HEIGHT   = 3;
float SCALE_WIDTH                   = 1;
float SCALE_HEIGHT                  = 1;

float dt;
sf::Time sec;
sf::RenderWindow window(sf::VideoMode(WINDOW_RESOLUTION_WIDTH, WINDOW_RESOLUTION_HEIGHT), "grachi");
sf::Font font;

void update_window(){
    window.display();
}
void clear_window(){
    window.clear();
}

std::string get_project_root_path() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string::size_type pos = std::string(path).find_last_of("\\/");
    return std::string(path).substr(0, pos);
}

std::string get_home_dir() {
    char* homePath = nullptr;
    std::string homeDir;
    size_t len;
    _dupenv_s(&homePath, &len, "USERPROFILE");
    homeDir = homePath ? std::string(homePath) : "";
    free(homePath);
    if(homeDir == "")
        throw std::runtime_error("Could not get home directory, please set the HOME flag.");
    return homeDir;
}

int main(int argc, char const *argv[]){

    // SCALE_WIDTH = scale_factor_calc();
    // SCALE_HEIGHT = scale_factor_calc();
    
    #ifdef DEBUG
    m_dbg("Debug is enabled");
    #endif
    m_nrm("Starting program", PROGRAM_INFO, FL_GRACHI, false);
    project_root_path = get_project_root_path();
    project_in_home_docs = get_home_dir() + "\\Documents\\grachi\\";
#ifdef DEBUG
    atrc_path = project_root_path + "\\assets\\data\\";
    image_path = project_root_path + "\\assets\\images\\";
    audio_path = project_root_path + "\\assets\\audio\\";
    std::string fontPath = project_root_path + "\\assets\\fonts\\clacon2.ttf";
    // std::string fontPath = project_root_path + "\\assets\\fonts\\ARIBLK.ttf";
#else
    atrc_path = project_in_home_docs + "\\assets\\data\\";
    image_path = project_in_home_docs + "\\assets\\images\\";
    audio_path = project_in_home_docs + "\\assets\\audio\\";
    std::string fontPath = project_in_home_docs + "\\assets\\fonts\\clacon2.ttf";
#endif
    if (!font.loadFromFile(fontPath)) {
        m_nrm("Error loading the font", FONT_ERROR, FL_GRACHI, true);
    }
    
    Airplane test;
    test.initialize_airplane("su25");

    main_state = main_states::in_main_menu;
    main_menu_state = main_menu_states::initialize;
    game_state = game_states::initialize;

    sf::Clock deltaClock = sf::Clock();
    sf::Clock other_clock = sf::Clock();
    window.setFramerateLimit(60);
    while (window.isOpen()){
        float dt = deltaClock.restart().asSeconds();
        sec = other_clock.getElapsedTime();
        switch (main_state) {
            case main_states::in_game:
                game_master_loop();
                break;
            case main_states::in_main_menu:
                main_menu_main_loop();
                break;
        }
    }
    
    return 0;
}




// #include <SFML/Graphics.hpp>
// #include <Windows.h>

// // Convert a wide Unicode string to an UTF8 string
// std::string utf8_encode(const std::wstring &wstr)
// {
//     if( wstr.empty() ) return std::string();
//     int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
//     std::string strTo( size_needed, 0 );
//     WideCharToMultiByte                  (CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
//     return strTo;
// }

// // Convert an UTF8 string to a wide Unicode String
// std::wstring utf8_decode(const std::string &str)
// {
//     if( str.empty() ) return std::wstring();
//     int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
//     std::wstring wstrTo( size_needed, 0 );
//     MultiByteToWideChar                  (CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
//     return wstrTo;
// }

// int main(){
//     auto context_settings = sf::ContextSettings();
//     auto window = sf::RenderWindow{ sf::VideoMode{{500, 500}}, "Hello World", sf::State::Windowed, context_settings};
//     window.setFramerateLimit(60);
//     auto font = sf::Font::openFromFile("C:\\Windows\\Fonts\\Arial.ttf").value();
//     auto text = sf::Text{ font };

//     std::string str = "привет";
//     std::wstring new_str = utf8_decode(str);
//     text.setString(new_str);

//     while (window.isOpen()){
//         while (auto event = window.pollEvent()) {
//             if (event.value().is<sf::Event::Closed>()){
//                 window.close();
//             }
//         }
//         window.clear();
//         window.draw(text);
//         window.display();
//     }
//     return 0;
// }