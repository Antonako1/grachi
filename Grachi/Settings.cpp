#include "Settings.hpp"
#include "Grachi.h"

Settings::Settings() {
	this->state = States::Video;
	this->previousState = (int)Grachi::States::MainMenu;
}

void Settings::Initialize(int previousState) {
	this->previousState = previousState;
}

Settings::~Settings() {

}

void Settings::UpdateLogics(){

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