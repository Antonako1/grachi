#pragma once
#ifndef GRACHI_H
#define GRACHI_H
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define _VERSION_ 1 // Increment with one when changing MAJOR.MINOR.PATCH

#include "Menu.hpp"
#include "Settings.hpp"
#include <ATRC.h>
#include "Common.hpp"
#include <stdint.h>
#include <vector>


// Default values if not changed via config files
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

#define SCREEN_WIDTH_MIN 1024
#define SCREEN_HEIGHT_MIN 768

#define TO_STR_HELPER(x) #x
#define TO_STR(x) TO_STR_HELPER(x)



class Entity {
public:
private:
};

class GroundVehicle : Entity {
public:
private:
};

class Airplane : Entity {
public:
private:
};

class Infantry : Entity {
public:
private:
};

class Location{
public:
private:
	std::vector<Infantry> infantry;
	std::vector<Airplane> airplanes;
	std::vector<GroundVehicle> groundVehicles;
};

class Map {
public:
private:
	std::vector<Location> locations;
};

class GameData {
public:
private:
	Map map;
};

#ifdef _MSC_VER
#   pragma pack(push, 1)
#endif
typedef struct _SavefileBinData {
	uint32_t game_version; // game version. 0xFFFFFF__
	// TODO...
}
#if defined(__GNUC__)
__attribute__((packed))
#endif
SavefileBinData;
#ifdef _MSC_VER
#   pragma pack(pop)
#endif

class Grachi {
public:
	enum class States {
		Exit = 0,
		
		InitMainMenu, // Initializes Menu class
		MainMenu, // Runs Menu class
		
		InitSettings, // Initializes Settings class
		Settings, // Runs Settings class
		

		InitCredits, // Initializes Credits class
		Credits, // Runs Credits class
		
		InitLoadGame, // Initializes RunGame with chosen game data
		InitContinue, // Initializes RunGame with previous game data or fresh if none
		InitStartGame, // Initializes RunGame with new data
		
		StartGame, // Runs the game with given data

		RunGame,

		StateAmount,
	};
	void SetState(States a_state) { this->state = a_state; }
	States GetState(void) const { return this->state; }

	Grachi();
	void InitializeRaylib();
	void BeginGame();
	void UpdateLogics();
	void DrawGame();
	void EndGame();
	~Grachi();


	int HandleArgs(int argc, char* argv[]);

	void setPrevState(prevState prev) { this->prevState = prev; }
	prevState getPrevState() const { return this->prevState; }

private:
	struct args {
		bool run_fullscreen;
	};


	prevState prevState;

	args args;
	float deltaTime;
	States state;
	Menu menu;
	Settings settings;

	bool raylibInitialized;

	int windowWidth;
	int windowHeight;
};

extern Grachi *GameInstance; // Global game instance for accessing state.

#endif // !GRACHI_H