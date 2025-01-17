#ifndef MSG_h
#define MSG_h

#include <string>

enum fl_numbers {
    FL_GRACHI = 0,
    FL_ATRC_FD,
    FL_AMOUNT,
    FL_AIRPLANE,
    FL_MAIN_MENU
};

enum msg_numbers {
    UNKNOWN_MESSAGE = 0,
    PROGRAM_INFO,
    FONT_ERROR,
    DATA_FILE_ERROR,
    DATA_VALUE_ERROR,
    ERROR_AMOUNT,
    LIST_OUT_OF_BOUNDS_ERROR,
    CAST_CONVERSION_ERROR,
    MATH_ERROR,
    IMAGE_ERROR,
};

void m_nrm(std::string sMsg, int iMsg, int fl, bool fatal);
void m_dbg(std::string msg);
void wm_dbg(std::wstring msg);

#endif // MSG_h