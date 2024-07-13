#ifndef HARDWARE_H
#define HARDWARE_H

struct mouse {
    size_t x = 0;
    size_t y = 0;
    bool ms_1_down = false;
    bool ms_2_down = false;
    bool ms_3_down = false;
};

struct keyboard {
    bool esc_down = false;
    bool w_down = false;
    bool a_down = false;
    bool s_down = false;
    bool d_down = false;
};

#endif // HARDWARE_H