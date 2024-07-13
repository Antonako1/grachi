#include <iostream>
#include <string>
#include "./msg.hpp"

#include <windows.h>

/*
1,20 = red
1,10=green
1,14 = yellow
*/
void set_colour(int text_colour, int bg_colour){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_colour << 4) | text_colour);
}

void reset_colour() { 
    set_colour(7, 0);
}

void m_dbg(std::string msg){
    set_colour(1, 5);
    std::cout << "~~DEBUG MSG: '" << msg << "'" << std::endl;
    reset_colour();
}

void wm_dbg(std::wstring msg){
    set_colour(1, 4);
    std::wcout << L"~~DEBUG MSG: '" << msg << "'" << std::endl;
    reset_colour();
}

void m_nrm(std::string sMsg, int iMsg, int fl, bool fatal){
    std::string func_generated = "";
    bool error_colouring = false;
    switch (iMsg)
    {
        case DATA_FILE_ERROR:
            func_generated = "Error accessing data file";
            error_colouring = true;
            break;
        case DATA_VALUE_ERROR:
            func_generated = "Error reading data";
            error_colouring = true;
            break;
        case PROGRAM_INFO:
            func_generated = "Message from program";
            break;
        case FONT_ERROR:
            func_generated = "Error with fonts";
            error_colouring = true;
            break;
        case LIST_OUT_OF_BOUNDS_ERROR:
            func_generated = "Program tried accessing list from out of bounds";
            error_colouring = true;
            break;
        case CAST_CONVERSION_ERROR:
            func_generated = "Error cast converting values";
            error_colouring = true;
            break;
        case MATH_ERROR:
            func_generated = "Error with mathematical calculations";
            error_colouring = true;
            break;
        default:
        case UNKNOWN_MESSAGE:
            func_generated = "Unknown message";
            break;
    }
    if(fatal||error_colouring) set_colour(1, 20);
    else set_colour(1, 225);
    std::cout << func_generated << ". '<" << fl << "-" << iMsg << ">' Provided info: '" << sMsg << "'"<< std::endl;
    reset_colour();

    if(fatal){
        exit(iMsg);
    }
}