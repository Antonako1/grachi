
#include "Grachi.h"
#include <Arghand.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raylib.h>
#include <string>
#include "CommonNon.hpp"

void Grachi::InitializeRaylib() {
    InitWindow(this->windowWidth, this->windowHeight, "Grachi");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    this->raylibInitialized = true;
}
Grachi::Grachi() {
    this->windowWidth = SCREEN_WIDTH;
    this->windowHeight = SCREEN_HEIGHT;
    // TODO: Apply args
    this->deltaTime = 0.15f;
    this->SetState(States::InitMainMenu);
    this->raylibInitialized = false;
}

void Grachi::BeginGame() {
    while (!WindowShouldClose()) {
        this->UpdateLogics(); // Updates global logic (deltatime etc.)
        switch (this->GetState()) {
        case States::InitMainMenu:
            this->menu = Menu();
            this->menu.InitializeRaylib();
            this->SetState(States::MainMenu);
            break;
        case States::MainMenu:
            this->menu.UpdateLogics();
            this->menu.Draw();
            break;
        case States::InitSettings:
            this->settings = Settings();
            this->settings.Initialize(this->getPrevState().Major);
            this->SetState(States::Settings);
            break;
        case States::Settings:
            this->settings.UpdateLogics();
            this->settings.Draw();
            break;
        case States::Exit:
        default:
            return; // exit function, triggering destructor inside main
        }
    }
}


void Grachi::UpdateLogics() {
    this->deltaTime = GetFrameTime();
}

void Grachi::DrawGame() {
    return;
}

void Grachi::EndGame() {
    if (this->raylibInitialized) {
        CloseWindow();
    }
}
Grachi::~Grachi() {
    this->EndGame();
}


int Grachi::HandleArgs(int argc, char* argv[]) {
    Arghand handler;
    std::vector<CmdOption> options = {
        CMD_OPTION("h", "help",     HelpOptionDefault,      "",           "Display help information"),
        CMD_OPTION("v", "",  VersionOptionDefault,   "",           "Display version information"),
        CMD_OPTION("", "fullscreen", NoInputDefault, "", "Launch in fullscreen mode"),
        CMD_OPTION("", "width", QSTU64(CmdOptionFlags::IsValueRequired), TO_STR(SCREEN_WIDTH), "Screen's starting width"),
        CMD_OPTION("", "height", QSTU64(CmdOptionFlags::IsValueRequired), TO_STR(SCREEN_HEIGHT), "Screen's starting height"),
    };

    handler.SetCmdOptions(options);
    handler.SetSeparator(',');
    handler.SetParserOptions((ParserOptions::StyleWindows | ParserOptions::HelpDisplayAll | ParserOptions::VersionDisplayFooter));

    handler.SetApplicationName("Grachi");
    handler.SetHelpHeader("Grachi - A Soviet-Afghan war based video game");
    handler.SetHelpFooter("\nMaintained at https://github.com/Antonako1/grachi.");
    handler.SetLicense("Licensed under the BSD-2-Clause License.");
    handler.SetVersion(handler.VersionNumToString(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH));
    handler.SetVersionFooter("Maintained at https://github.com/Antonako1/grachi.");

    Arghand::ParseResult res = handler.parse(argc, argv);
    if (res == Arghand::ParseResult::Error || res == Arghand::ParseResult::MissingValue) {
        std::cerr << "Error parsing command line arguments." << std::endl;
        return 1;
    }

    if (res == Arghand::ParseResult::SuccessWithHelp || res == Arghand::ParseResult::SuccessWithVersion) { 
        return 2; 
    }

    if (handler["fullscreen"]) {
        this->args.run_fullscreen = true;
    }
    if (handler["width"]) {
        this->windowWidth = TextToInteger(handler.GetValue("width").c_str());
    }
    if (handler["height"]) {
        this->windowWidth = TextToInteger(handler.GetValue("height").c_str());
    }
    return 0;
}

Grachi* GameInstance;


std::string BASE_PATH;

int main(int argc, char *argv[])
{   
    Grachi game = Grachi();
    if (int arg_res = game.HandleArgs(argc, argv) != 0) {
        std::cout << "Exited via argument handling with exit code " << arg_res << std::endl;
        return arg_res;
    }
       
    BASE_PATH = GetExecutableDir();

    GameInstance = &game;
    game.InitializeRaylib();
    game.BeginGame();
	return 0;
}
