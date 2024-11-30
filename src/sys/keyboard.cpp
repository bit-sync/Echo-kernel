#include "keyboard.h"
#include "display.h"
#include "../types.h"

extern "C" void keyboard_handler(void);
extern "C" char read_port(unsigned short port);
extern "C" void write_port(unsigned short port, unsigned char data);
extern "C" void load_idt(unsigned long *idt_ptr);

namespace keyboard {
    #define IDT_SIZE 256
    #define KEYBOARD_DATA_PORT 0x60
    #define KEYBOARD_STATUS_PORT 0x64
    #define INTERRUPT_GATE 0x8e
    #define KERNEL_CODE_SEGMENT_OFFSET 0x08

    struct IDT_entry {
        unsigned short int offset_lowerbits;
        unsigned short int selector;
        unsigned char zero;
        unsigned char type_attr;
        unsigned short int offset_higherbits;
    };

    struct IDT_entry IDT[IDT_SIZE];
    
    // Buffer for storing input
    static char input_buffer[MAX_INPUT_LENGTH];
    static unsigned int buffer_pos = 0;
    static bool input_ready = false;
    static bool waiting_for_input = false;

    /* Keyboard map for US QWERTY keyboard */
    static unsigned char keyboard_map[128] = {
        0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '0', '-', '=', '\b',
        '\t',
        'q', 'w', 'e', 'r',
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0,
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
        '\'', '`',   0,
        '\\', 'z', 'x', 'c', 'v', 'b', 'n',
        'm', ',', '.', '/',   0,
        '*',
        0,  /* Alt */
        ' ',  /* Space bar */
        0,  /* Caps lock */
        0,  /* F1 key ... > */
        0,   0,   0,   0,   0,   0,   0,   0,
        0,  /* < ... F10 */
        0,  /* Num lock*/
        0,  /* Scroll Lock */
        0,  /* Home key */
        0,  /* Up Arrow */
        0,  /* Page Up */
        '-',
        0,  /* Left Arrow */
        0,
        0,  /* Right Arrow */
        '+',
        0,  /* End key*/
        0,  /* Down Arrow */
        0,  /* Page Down */
        0,  /* Insert Key */
        0,  /* Delete Key */
        0,   0,   0,
        0,  /* F11 Key */
        0,  /* F12 Key */
        0,  /* All other keys are undefined */
    };

    bool idt_init(void) {
        unsigned long keyboard_address;
        unsigned long idt_address;
        unsigned long idt_ptr[2];

        /* populate IDT entry of keyboard's interrupt */
        keyboard_address = (unsigned long)keyboard_handler;
        IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
        IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
        IDT[0x21].zero = 0;
        IDT[0x21].type_attr = INTERRUPT_GATE;
        IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

        /* ICW1 - begin initialization */
        write_port(0x20 , 0x11);
        write_port(0xA0 , 0x11);

        /* ICW2 - remap offset address of IDT */
        write_port(0x21 , 0x20);
        write_port(0xA1 , 0x28);

        /* ICW3 - setup cascading */
        write_port(0x21 , 0x00);
        write_port(0xA1 , 0x00);

        /* ICW4 - environment info */
        write_port(0x21 , 0x01);
        write_port(0xA1 , 0x01);

        /* mask interrupts */
        write_port(0x21 , 0xff);
        write_port(0xA1 , 0xff);

        /* fill the IDT descriptor */
        idt_address = (unsigned long)IDT;
        idt_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
        idt_ptr[1] = idt_address >> 16;

        load_idt(idt_ptr);
        kb_init();
        return true;
    }

    void kb_init(void) {
        /* 0xFD is 11111101 - enables only IRQ1 (keyboard) */
        write_port(0x21, 0xFD);
    }

    void kb_disable(void) {
        write_port(0x21, 0xFF);
    }

    char* get_input(const char* prompt) {
        // Print prompt if provided
        if (prompt) {
            display::print(prompt);
        }

        // Reset input state
        buffer_pos = 0;
        input_ready = false;
        waiting_for_input = true;
        
        // Wait for input to be ready (Enter key pressed)
        while (!input_ready) {
            // CPU can take a break while waiting
            asm volatile("hlt");
        }
        
        waiting_for_input = false;
        input_buffer[buffer_pos] = '\0';  // Null terminate the string
        return input_buffer;
    }

    
}

extern "C" void keyboard_handler_main(void) {
    unsigned char status;
    char keycode;

    /* write EOI */
    write_port(0x20, 0x20);

    status = read_port(KEYBOARD_STATUS_PORT);
    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if(keycode < 0 || keycode >= 128) return;

        // Only handle key press events (ignore key releases)
        if(keycode & 0x80) return;

        char key = keyboard::keyboard_map[(unsigned char) keycode];
        
        // Only process input if we're waiting for it
        if (keyboard::waiting_for_input && key) {
            if (key == '\n') {
                // Enter key pressed, mark input as ready
                display::print("\n");
                keyboard::input_ready = true;
            }
            else if (key == '\b' && keyboard::buffer_pos > 0) {
                // Handle backspace
                keyboard::buffer_pos--;
                display::backspace();  // Use our new backspace function
            }
            else if (keyboard::buffer_pos < keyboard::MAX_INPUT_LENGTH - 1 && key != '\b') {
                // Add character to buffer and display it
                keyboard::input_buffer[keyboard::buffer_pos++] = key;
                char str[2] = {key, '\0'};
                display::print(str);
            }
        }
    }
}