#include "Settings.hpp"
#include "Grachi.h"

Settings::Settings() {
	this->state = States::Video;
	this->previousState = (int)Grachi::States::MainMenu;
	this->changesMade = false;
}

void Settings::Initialize(int previousState) {
	this->previousState = previousState;
}

Settings::~Settings() {

}

#include <iostream>
void Settings::backToPreviousScreen() const {
	GameInstance->SetState((Grachi::States)this->previousState);
}

void Settings::UpdateLogics(){
	if (IsKeyPressed(KEY_ESCAPE))
		this->backToPreviousScreen();
}
void Settings::Draw() {
	BeginDrawing();
	ClearBackground(GRAY);

	switch (this->state) {
	case States::Video:
	case States::Audio:
	case States::Controls:
	default:
		break;
	}

	EndDrawing();
}