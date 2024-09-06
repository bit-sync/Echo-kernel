#ifndef DISPLAY_H
#define DISPLAY_H

#define DPCL_BLACK            0x00
#define DPCL_BLUE             0x01
#define DPCL_GREEN            0x02
#define DPCL_CYAN             0x03
#define DPCL_RED              0x04
#define DPCL_MAGENTA          0x05
#define DPCL_BROWN            0x06
#define DPCL_LIGHT_GREY       0x07
#define DPCL_DARK_GREY        0x08
#define DPCL_LIGHT_BLUE       0x09
#define DPCL_LIGHT_GREEN      0x10
#define DPCL_LIGHT_CYAN       0x11
#define DPCL_LIGHT_RED        0x12
#define DPCL_LIGHT_MAGENTA    0x13
#define DPCL_LIGHT_BROWN      0x14
#define DPCL_WHITE            0x0f

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES


unsigned int current_loc = 0;
char *vidptr = (char*)0xb8000;

/*Prints newline to screen manually (\n also returns newline)*/
void print_newline(void)
{
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

/*Clears screen of current text*/
void clear_screen(void)
{
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
}

/*Prints given string - print newline with: \n*/
void print(const char *str)
{
    unsigned int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            print_newline();
        } else {
            vidptr[current_loc++] = str[i];
            vidptr[current_loc++] = 0x07;
        }
        i++;
    }
}
/*Print text with color (Similer to "print()")*/
void printc(const char *str, const char* color) {
    unsigned int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            print_newline();
        } else {
            vidptr[current_loc++] = str[i];
            vidptr[current_loc++] = color;
        }
        i++;
    }
}

#endif /* PRINT_UTILS_H */