#include "display.h"

namespace display {
    /* there are 25 lines each of 80 columns; each element takes 2 bytes */
    #define LINES 25
    #define COLUMNS_IN_LINE 80
    #define BYTES_FOR_EACH_ELEMENT 2
    #define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

    /* current cursor location */
    static unsigned int current_loc = 0;
    /* video memory begins at address 0xb8000 */
    static char * const vidptr = (char*)0xb8000;

    void print_newline(void)
    {
        unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
        current_loc = current_loc + (line_size - current_loc % (line_size));
        
        // Scroll if we're at the bottom of the screen
        if (current_loc >= SCREENSIZE) {
            // Move everything up one line
            for (unsigned int i = 0; i < SCREENSIZE - line_size; i++) {
                vidptr[i] = vidptr[i + line_size];
            }
            // Clear the last line
            for (unsigned int i = SCREENSIZE - line_size; i < SCREENSIZE; i++) {
                vidptr[i] = (i % 2) ? 0x07 : ' ';
            }
            current_loc -= line_size;
        }
    }

    void print(const char *str)
    {
        if (!str) return;
        
        unsigned int i = 0;
        while (str[i] != '\0' && current_loc < SCREENSIZE) {
            if (str[i] == '\n') {
                print_newline();
            } else {
                vidptr[current_loc++] = str[i];
                vidptr[current_loc++] = 0x07;  // Default light grey on black
            }
            i++;
        }
    }

    void printc(const char *str, unsigned char color)
    {
        if (!str) return;
        
        unsigned int i = 0;
        while (str[i] != '\0' && current_loc < SCREENSIZE) {
            if (str[i] == '\n') {
                print_newline();
            } else {
                vidptr[current_loc++] = str[i];
                vidptr[current_loc++] = color;  // Use the specified color
            }
            i++;
        }
    }

    void clear_screen(void)
    {
        unsigned int i = 0;
        while (i < SCREENSIZE) {
            vidptr[i++] = ' ';
            vidptr[i++] = 0x07;
        }
        current_loc = 0;
    }

    void backspace(void)
    {
        if (current_loc >= 2) {  // Make sure we have space to move back
            current_loc -= 2;  // Move back one character (2 bytes)
            vidptr[current_loc] = ' ';     // Clear the character
            vidptr[current_loc + 1] = 0x07;  // Set the attribute byte
        }
    }
}