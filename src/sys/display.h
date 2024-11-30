#ifndef DISPLAY_H
#define DISPLAY_H

namespace display {
    /* Color definitions */
    constexpr unsigned char CL_BLACK         = 0x00;
    constexpr unsigned char CL_BLUE          = 0x01;
    constexpr unsigned char CL_GREEN         = 0x02;
    constexpr unsigned char CL_CYAN          = 0x03;
    constexpr unsigned char CL_RED           = 0x04;
    constexpr unsigned char CL_MAGENTA       = 0x05;
    constexpr unsigned char CL_BROWN         = 0x06;
    constexpr unsigned char CL_LIGHT_GREY    = 0x07;
    constexpr unsigned char CL_DARK_GREY     = 0x08;
    constexpr unsigned char CL_LIGHT_BLUE    = 0x09;
    constexpr unsigned char CL_LIGHT_GREEN   = 0x0A;
    constexpr unsigned char CL_LIGHT_CYAN    = 0x0B;
    constexpr unsigned char CL_LIGHT_RED     = 0x0C;
    constexpr unsigned char CL_LIGHT_MAGENTA = 0x0D;
    constexpr unsigned char CL_YELLOW        = 0x0E;
    constexpr unsigned char CL_WHITE         = 0x0F;

    /* Screen constants */
    constexpr unsigned int LINES = 25;
    constexpr unsigned int COLUMNS_IN_LINE = 80;
    constexpr unsigned int BYTES_FOR_EACH_ELEMENT = 2;
    constexpr unsigned int SCREENSIZE = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES;

    void clear_screen(void);
    void print(const char *str);
    void printc(const char *str, unsigned char color);  
    void print_newline(void);
    void backspace(void);  
}

#endif // DISPLAY_H
