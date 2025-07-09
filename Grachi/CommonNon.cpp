#include "CommonNon.hpp"
#include <filesystem>
#ifdef WIN32
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