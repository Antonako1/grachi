#pragma once
#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#include <raygui.h>

class Settings {
public:
	Settings();
	~Settings();
	void Initialize(int previousState);

	enum class States {
		Video = 0,
		Audio,
		Controls,
		Amount,
	};

	void SetState(States a_state) { this->state = a_state; }
	States GetState() const { return this->state; }

	void Draw();
	void UpdateLogics();

private:
	States state;
	int previousState;
};

#endif // SETTINGS_HPP