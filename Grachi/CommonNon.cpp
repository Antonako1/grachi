#include "CommonNon.hpp"
#include <filesystem>
#include <cstdlib>


#ifdef WIN32
#include <userenv.h>
#include <windows.h>
std::string GetExecutablePath() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return std::string(path);
}

#else 
#include <unistd.h>
#include <limits.h>

std::string GetExecutablePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
}
#endif
std::string GetExecutableDir() {
    std::string fullPath = GetExecutablePath();
    return std::filesystem::path(fullPath).parent_path().string();
}

std::string GetAppdata() {
#ifdef _WIN32
    const char* homeDrive = std::getenv("HOMEDRIVE");
    const char* homePath = std::getenv("HOMEPATH");
    const char* userProfile = std::getenv("USERPROFILE");

    if (userProfile)
        return std::string(userProfile);
    else if (homeDrive && homePath)
        return std::string(homeDrive) + homePath;
    else
        return ""; // Couldn't determine home path
#else
    const char* home = std::getenv("HOME");
    if (home)
        return std::string(home);
    else
        return ""; // Couldn't determine home path
#endif
}