#pragma once
#ifndef COMMONNON_HPP
#define COMMONNON_HPP
#include <string>
std::string GetExecutableDir();
std::string GetExecutablePath();

constexpr auto BACK_TO_DIR = "/../../../../";
extern std::string BASE_PATH;

#define AUTO_PATH(x) BASE_PATH + BACK_TO_DIR + x

#endif // COMMONNON_HPP

