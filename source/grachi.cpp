#include <iostream>
#include <windows.h>
#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <ATRC.h>
#include "./grachi.hpp"
#include "./states.hpp"
#include "./screens/screens.hpp"
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

float dt;
sf::Time sec;
sf::RenderWindow window(sf::VideoMode(1024, 768), "grachi");
sf::Font font;

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
    #ifdef DEBUG
    m_dbg("Debug is enabled");
    #endif
    m_nrm("Starting program", PROGRAM_INFO, FL_GRACHI, false);
    project_root_path = get_project_root_path();
    project_in_home_docs = get_home_dir() + "\\Documents\\grachi\\";
#ifdef DEBUG
    atrc_path = project_root_path + "\\assets\\data\\";
    image_path = project_root_path + "\\assets\\images";
    audio_path = project_root_path + "\\assets\\audio\\";
    std::string fontPath = project_root_path + "\\assets\\fonts\\clacon2.ttf";
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
    while (window.isOpen()){
        float dt = deltaClock.restart().asSeconds();
        sec = other_clock.getElapsedTime();
        switch (main_state) {
            case main_states::in_game:
                break;
            case main_states::in_main_menu:
                main_menu_main_loop();
                break;
        }
    }
    
    return 0;
}
