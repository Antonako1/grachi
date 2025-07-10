#include "Menu.hpp"
#include <raygui.h>
#include <raylib.h>
#include <cstring>
#include <iostream>
#include "Grachi.h"
#include "CommonNon.hpp"

Menu::Menu() {
	this->bg_colour = GRAY;
	this->bg_img = { 0 };

}
void Menu::InitializeRaylib() {
	std::string path = AUTO_PATH("assets/img1.png");
	this->bg_img = LoadTexture(path.c_str());

	this->buttons.clear();
	float width = DEFAULT_BTN_WIDTH;
	float height = DEFAULT_BTN_HEIGHT;
	float x = ((float)GetScreenWidth() / 2.f) - (width / 2.f);

	// calculate button list height
	float buttons_to_be_made = (float)BtnIds::ButtonAmount;
	float total_height = 0.f;
	for (float i = 0; i < buttons_to_be_made; i++) {
		B_I(total_height, height);
	}

	// calculate starting y-axis
	float y = ((float)GetScreenHeight() - total_height) / 2;

	this->buttons = {
		{{x,     y,          width, height}, "Continue", (int)BtnIds::Continue},
		{{x, B_I(y, height), width, height}, "Start game", (int)BtnIds::StartGame},
		{{x, B_I(y, height), width, height}, "Load game", (int)BtnIds::LoadGame},
		{{x, B_I(y, height), width, height}, "Settings", (int)BtnIds::Settings},
		{{x, B_I(y, height), width, height}, "Credits", (int)BtnIds::Credits},
		{{x, B_I(y, height), width, height}, "Exit", (int)BtnIds::Exit},
	};
}
Menu::~Menu() {
	UnloadTexture(this->bg_img);
}

void Menu::UpdateLogics() {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 pos = GetMousePosition();
		for (int i = 0; i < (int)BtnIds::ButtonAmount; i++) {
			button_data* cur = &this->buttons[i];
			if (CheckCollisionPointRec(pos, cur->rect)) {
				switch (BtnIds(cur->id)) {
				case BtnIds::Continue:
					GameInstance->setPrevState({ (int)GameInstance->GetState(), -1 });
					GameInstance->SetState(Grachi::States::InitContinue);
					break;
				case BtnIds::StartGame:
					GameInstance->setPrevState({ (int)GameInstance->GetState(), -1 });
					GameInstance->SetState(Grachi::States::InitStartGame);
					break;
				case BtnIds::LoadGame:
					GameInstance->setPrevState({ (int)GameInstance->GetState(), -1 });
					GameInstance->SetState(Grachi::States::InitLoadGame);
					break;
				case BtnIds::Settings:
					GameInstance->setPrevState({ (int)GameInstance->GetState(), -1 });
					GameInstance->SetState(Grachi::States::InitSettings);
					break;
				case BtnIds::Credits:
					GameInstance->setPrevState({ (int)GameInstance->GetState(), -1 });
					GameInstance->SetState(Grachi::States::InitCredits);
					break;
				case BtnIds::Exit:
				default:
					GameInstance->setPrevState({ (int)GameInstance->GetState(), -1 });
					GameInstance->SetState(Grachi::States::Exit);
					break;
				}
			}
		}
	}
}

void Menu::Draw() {
	BeginDrawing();
	ClearBackground(this->bg_colour);
	if (IsTextureValid(this->bg_img))
		DrawTexture(this->bg_img, 0, 0, WHITE);

	for (int i = 0; i < (float)BtnIds::ButtonAmount; i++) {
		button_data *cur = &this->buttons[i];
		GuiButton(cur->rect, cur->text);
	}

	EndDrawing();
}