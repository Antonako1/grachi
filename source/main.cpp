#include "main.h"
#include <iostream>
#include <Arghand.h>

sf::RenderWindow WINDOW; // defined in graphic.h
StateLocation CURRENT_STATE = StateLocation::MainMenu; // defined in main.h
GameState CURRENT_GAME_STATE = GameState::None; // defined in main.h
MainMenuState CURRENT_MAIN_MENU_STATE = MainMenuState::None; // defined in main.h
SettingsState CURRENT_SETTINGS_STATE = SettingsState::None; // defined in main.h



int main(int argc, char* argv[]) {
    Arghand handler;
    std::vector<CmdOption> options = {
        CMD_OPTION("h", "help",     HelpOptionDefault,      "",           "Display help information"),
        CMD_OPTION("v", "version",  VersionOptionDefault,   "",           "Display version information"),
    };
    handler.SetCmdOptions(options);
    handler.SetSeparator(',');

    handler.SetParserOptions(
        (ParserOptions::DefaultOptions |
        ParserOptions::VersionDisplayFooter ) & 
        ~(ParserOptions::HelpDisplayAppName | 
        ParserOptions::HelpDisplayVersion) 
    );

    handler.SetApplicationName("Grachi");
    handler.SetHelpHeader("Usage: \n\tGrachi [options]\n");
    handler.SetHelpFooter("\nMaintained at https://github.com/Antonako1/grachi.");
    handler.SetLicense("Licensed under the BSD-2-Clause License.");
    handler.SetVersion(handler.VersionNumToString(1, 0, 0));
    handler.SetVersionFooter("Maintained at https://github.com/Antonako1/grachi.");
    
    Arghand::ParseResult res = handler.parse(argc, argv);
    if(res == Arghand::ParseResult::Error){
        std::cerr << "Error parsing command line arguments." << std::endl;
        return 1;
    }
    if(res == Arghand::ParseResult::Success){
        
    } else if(res == Arghand::ParseResult::SuccessWithHelp || res == Arghand::ParseResult::SuccessWithVersion) {
        return 0;
    }



    // Initialize the SFML window
    WINDOW = sf::RenderWindow{
        sf::VideoMode{{800u, 600u}}, "Grachi",
    };

    while (WINDOW.isOpen()) {
        // State machine handling
        switch (CURRENT_STATE) {
            case StateLocation::MainMenu:
                // Handle main menu logic
                if (CURRENT_MAIN_MENU_STATE == MainMenuState::StartGame) {
                    CURRENT_STATE = StateLocation::Game;
                    CURRENT_GAME_STATE = GameState::StartFreshGame; // Set initial game state
                } else if (CURRENT_MAIN_MENU_STATE == MainMenuState::ContinueGame) {
                    CURRENT_STATE = StateLocation::Game;
                    CURRENT_GAME_STATE = GameState::ContinueGame; // Set initial game state
                } else if (CURRENT_MAIN_MENU_STATE == MainMenuState::OpenSettings) {
                    CURRENT_STATE = StateLocation::Settings;
                } else if (CURRENT_MAIN_MENU_STATE == MainMenuState::LoadSavedGame) {
                    CURRENT_STATE = StateLocation::LoadSavedGame;
                }  else if (CURRENT_MAIN_MENU_STATE == MainMenuState::ExitGame) {
                    WINDOW.close();
                }
                break;

            case StateLocation::Game:
                // Handle game logic
                if (CURRENT_GAME_STATE == GameState::ExitGame) {
                    WINDOW.close();
                }
                break;

            case StateLocation::Settings:
                // Handle settings logic
                if (CURRENT_SETTINGS_STATE == SettingsState::BackToMainMenu) {
                    CURRENT_STATE = StateLocation::MainMenu;
                    CURRENT_MAIN_MENU_STATE = MainMenuState::None; // Reset state
                }
                break;

            case StateLocation::Exit:
                WINDOW.close();
                break;

            default:
                break;
        }

        // while (const std::optional event = WINDOW.pollEvent()){
        //     if (event->is<sf::Event::Closed>())
        //         WINDOW.close();
        // }
        // WINDOW.clear();
        // WINDOW.display();
    }

    return 0;
}
