#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

extern sf::RenderWindow WINDOW; // defined in main.cpp




// For state machines

// Screen states for the game
enum class StateLocation {
    MainMenu,
    LoadSavedGame,
    Game,
    Settings,
    Exit
};
extern StateLocation CURRENT_STATE; // defined in main.cpp

// For game state management
enum class GameState {
    None,
    StartFreshGame,
    ContinueGame,
    OpenSettings,
    ExitGame
};
extern GameState CURRENT_GAME_STATE; // defined in main.cpp

// For main menu state management
enum class MainMenuState {
    None,
    StartGame,
    LoadSavedGame,
    ContinueGame,
    OpenSettings,
    ExitGame
};
extern MainMenuState CURRENT_MAIN_MENU_STATE; // defined in main.cpp

// For settings state management
enum class SettingsState {
    None,
    ChangeResolution,
    ChangeVolume,
    BackToMainMenu
};
extern SettingsState CURRENT_SETTINGS_STATE; // defined in main.cpp

#endif // MAIN_H