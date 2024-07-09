#include <iostream>
#include <windows.h>
#include <sfml/Window.hpp>
#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
#include "./grachi.hpp"
#include "./msg.hpp"
#include "./styling.hpp"
#include "./atrc_fd.hpp"
#include <ATRC.h>

h1 s_h1;
h2 s_h2;
h3 s_h3;
p  s_p;
std::string project_root_path;
std::string atrc_path;

std::string get_project_root_path() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string::size_type pos = std::string(path).find_last_of("\\/");
    return std::string(path).substr(0, pos);
}

int main(int argc, char const *argv[]){
    #ifdef DEBUG
    m_dbg("Debug is enabled");
    #endif

    m_nrm("Starting program", PROGRAM_INFO, FL_GRACHI, false);
    
    project_root_path = get_project_root_path();
    atrc_path = project_root_path + "\\assets\\data\\";
    initialize_asset_data();


    sf::RenderWindow window(sf::VideoMode(800, 600), "grachi");
    sf::Font font;

    std::string fontPath = project_root_path + "\\assets\\fonts\\clacon2.ttf";
    if (!font.loadFromFile(fontPath)) {
        m_nrm("Error loading the font", FONT_ERROR, FL_GRACHI, true);
    }



    std::string str="Русский текст тут абв!";
    m_dbg(str);
    
    // sf::String d_text;
    sf::Text text = sf::Text(str, font, s_p.f_sz);
    // text.setString(L"СУХОЙ 25");
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
 
        // Clear screen
        window.clear();

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }

    return 0;
}
