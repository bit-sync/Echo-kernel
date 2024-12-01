#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace keyboard {
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
    constexpr unsigned char CL_LIGHT_GREEN   = 0x10;
    constexpr unsigned char CL_LIGHT_CYAN    = 0x11;
    constexpr unsigned char CL_LIGHT_RED     = 0x12;
    constexpr unsigned char CL_LIGHT_MAGENTA = 0x13;
    constexpr unsigned char CL_LIGHT_BROWN   = 0x14;
    constexpr unsigned char CL_WHITE         = 0x0f;

    bool idt_init(void);
    void kb_init(void);
    void kb_disable(void);
    void keyboard_handler_main(void);
    
    // Maximum input length for get_input
    constexpr unsigned int MAX_INPUT_LENGTH = 256;
    
    // Get input from keyboard, similar to Python's input()
    // Returns the string entered by the user (terminated by Enter key)
    char* get_input(const char* prompt = nullptr);
}

#endif // KEYBOARD_H
