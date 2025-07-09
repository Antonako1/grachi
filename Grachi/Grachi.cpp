
#include "Grachi.h"
#include <Arghand.h>
#include <ATRC.h>



int main(int argc, char *argv[])
{
	Arghand handler;
    std::vector<CmdOption> options = {
        CMD_OPTION("h", "help",     HelpOptionDefault,      "",           "Display help information"),
        CMD_OPTION("v", "",  VersionOptionDefault,   "",           "Display version information"),
        CMD_OPTION("o", "output",   InputDefault,           "output.txt", "Specify output file"),
        CMD_OPTION("l", "list",     ListInputDefault,       "a,b",           "Specify a list of values (comma-separated)"),
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
    if (res != Arghand::ParseResult::SuccessWithHelp || res != Arghand::ParseResult::SuccessWithVersion) {

    }

	std::cout << "Hello CMake.\n";


	return 0;
}
