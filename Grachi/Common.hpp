#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

#include <raygui.h>

#define BUTTON_MAX_STR_LENGTH 64

// Struct for GuiButton
typedef struct button_data {
    Rectangle rect;
    char text[BUTTON_MAX_STR_LENGTH];
    int id;
} button_data;

// BUTTON_INCREMENT. Increments Y value with buttons height * 1.5
#define B_I(y, height) y += height * 1.5f
#define DEFAULT_BTN_WIDTH 250
#define DEFAULT_BTN_HEIGHT 40

struct prevState {
	int Major;
	int Minor;
};


#endif // COMMON_HPP
