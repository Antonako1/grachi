
#include "Grachi.h"
#include <Arghand.h>
#include <ATRC.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <raylib.h>

int main(int argc, char *argv[])
{
	Arghand handler;
    std::vector<CmdOption> options = {
        CMD_OPTION("h", "help",     HelpOptionDefault,      "",           "Display help information"),
        CMD_OPTION("v", "",  VersionOptionDefault,   "",           "Display version information"),
    };
    handler.SetCmdOptions(options);
    handler.SetSeparator(',');
    handler.SetParserOptions((ParserOptions::DefaultOptions | ParserOptions::VersionDisplayFooter));
      
    handler.SetApplicationName("Grachi");
    handler.SetHelpHeader("Grachi - Soviet-Afghan war based video game");
    handler.SetHelpFooter("\nMaintained at https://github.com/Antonako1/grachi.");
    handler.SetLicense("Licensed under the BSD-2-Clause License.");
    handler.SetVersion(handler.VersionNumToString(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH));
    handler.SetVersionFooter("Maintained at https://github.com/Antonako1/grachi.");

    Arghand::ParseResult res = handler.parse(argc, argv);
    if (res == Arghand::ParseResult::Error) {
        std::cerr << "Error parsing command line arguments." << std::endl;
        return 1;
    }
    if (res != Arghand::ParseResult::SuccessWithHelp && res != Arghand::ParseResult::SuccessWithVersion) {

    }

	std::cout << "Hello CMake.\n";


    InitWindow(800, 600, "Raylib + Raygui in Visual Studio");
    SetTargetFPS(60);

    float slider = 50.0f;
    bool toggle = true;
    char text[64] = "Hello, Raygui!";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        GuiLabel({ 20, 20, 200, 20 }, "Visual Studio + Raylib + Raygui");
        GuiSlider({ 20, 60, 200, 20 }, "Min", "Max", &slider, 0, 100);
        toggle = GuiCheckBox({ 20, 100, 20, 20 }, "Enable?", &toggle);
        GuiTextBox({ 20, 140, 200, 30 }, text, 64, true);

        EndDrawing();
    }

    CloseWindow();
	return 0;
}
