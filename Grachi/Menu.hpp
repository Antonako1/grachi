/// Main menu screen
#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <raygui.h>
#include "Common.hpp"

class Menu {
public:
    Menu();
    void InitializeRaylib();
    ~Menu();
    void UpdateLogics();
    void Draw();

    enum class BtnIds {
        Continue = 0,
        StartGame,
        LoadGame,
        Settings,
        Credits,
        Exit,
        ButtonAmount,
    };
private:
    std::vector<button_data> buttons;
    Color bg_colour;
    Texture2D bg_img;
};

#endif // MENU_HPP
