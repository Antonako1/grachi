#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <webview/webview.h>
extern webview::webview *WEBVIEW; // defined in main.cpp
#define webview_acc(code) \
    if(WEBVIEW == nullptr) { \
        throw std::runtime_error("WEBVIEW is not initialized!"); \
    } else { \
        code; \
    }
// For state machines

// Screen states for the game
enum class StateLocation {
    MainMenu,
    Game,
    Settings,
    Exit
};
extern StateLocation CURRENT_STATE; // defined in main.cpp

// For main menu state management
enum class MainMenuState {
    None,
    Initialize,
    DrawMenu,
    HandleEvents,
    StartGame,
    LoadSavedGame,
    ContinueGame,
    OpenSettings,
    ExitGame
};
extern MainMenuState CURRENT_MAIN_MENU_STATE; // defined in main.cpp


class MainMenu {
public:
    MainMenu();
    ~MainMenu();
    void Initialize();
    void Draw();
    void HandleEvents();
private:
};
extern MainMenu MAIN_MENU; // defined in main.cpp



#endif // MAIN_H