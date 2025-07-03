#include "resources.h"
#include <stdexcept>

atrc::ATRC_FD CONFIG_FILE; // Configuration file handler. Defined in resources.h

void loadResources() {
    // Load configuration file
    std::string configPath = "config.atrc"; // Path to the configuration file
    CONFIG_FILE.Read(configPath, ATRC_READ_ONLY);
    if (!CONFIG_FILE.CheckStatus()) {
        throw std::runtime_error("Failed to open configuration file.");
    }

}