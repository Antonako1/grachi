#pragma once
#ifndef COMMONNON_HPP
#define COMMONNON_HPP
#include <string>
std::string GetExecutableDir();
std::string GetExecutablePath();
std::string GetAppdataPath();

constexpr auto BACK_TO_DIR = "/../../../../";
extern std::string BASE_PATH;
extern std::string _APPDATA_PATH;

#define AUTO_PATH(x) BASE_PATH + BACK_TO_DIR + x
#define ASSET_PATH(x) BASE_PATH + BACK_TO_DIR + x
#define APPDATA_PATH(x) 
#endif // COMMONNON_HPP

