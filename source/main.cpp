#include <webview/webview.h>
#include <Arghand.h>
#include "main.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

webview::webview* WEBVIEW = nullptr; // Global webview instance

int main(int argc, char* argv[]) {
    Arghand handler;
    std::vector<CmdOption> options = {
        CMD_OPTION("h", "help",     HelpOptionDefault,      "",           "Display help information"),
        CMD_OPTION("v", "version",  VersionOptionDefault,   "",           "Display version information"),
    };
    handler.SetCmdOptions(options);
    handler.SetSeparator(',');
    
    handler.SetParserOptions(
        (ParserOptions::DefaultOptions |
        ParserOptions::VersionDisplayFooter ) & 
        ~(ParserOptions::HelpDisplayAppName | 
        ParserOptions::HelpDisplayVersion) 
    );
    
    handler.SetApplicationName("Grachi");
    handler.SetHelpHeader("Usage: \n\tGrachi [options]\n");
    handler.SetHelpFooter("\nMaintained at https://github.com/Antonako1/grachi.");
    handler.SetLicense("Licensed under the BSD-2-Clause License.");
    handler.SetVersion(handler.VersionNumToString(1, 0, 0));
    handler.SetVersionFooter("Maintained at https://github.com/Antonako1/grachi.");
    
    Arghand::ParseResult res = handler.parse(argc, argv);
    if(res == Arghand::ParseResult::Error){
        std::cerr << "Error parsing command line arguments." << std::endl;
        return 1;
    }
    if(res == Arghand::ParseResult::Success){
        
    } else if(res == Arghand::ParseResult::SuccessWithHelp || res == Arghand::ParseResult::SuccessWithVersion) {
        return 0;
    }


    std::ifstream html_fstream;
    try {
        
        // read the HTML file
        std::string html = std::filesystem::path("../html/index.html").string();
        if (!std::filesystem::exists(html)) {
            std::cerr << "HTML file not found: " << html << '\n';
            return 1;
        }

        // Load the HTML content
        html_fstream = std::ifstream(html);
        if (!html_fstream.is_open()) {
            std::cerr << "Failed to open HTML file: " << html << '\n';
            return 1;
        }
        std::string line;
        std::string html_content;
        while (std::getline(html_fstream, line)) {
            html_content += line + '\n';
        }

        if (html_content.empty()) {
            std::cerr << "Failed to read HTML file: " << html << '\n';
            return 1;
        }

        webview::webview w(true, nullptr);
        WEBVIEW = &w;
        WEBVIEW->set_title("Grachi");
        WEBVIEW->set_title("Grachi");
        WEBVIEW->set_size(1024, 768, WEBVIEW_HINT_FIXED);
        WEBVIEW->set_html(html_content);
        WEBVIEW->run();
        
    } catch (const webview::exception &e) {
        std::cerr << e.what() << '\n';
        html_fstream.close();
        return 1;
    }
    html_fstream.close();
    return 0;
}