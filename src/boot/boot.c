#include "../include/io.h"
#include "../main.c"

void main(void) {
	print("Hello, world!\n");
	printc("Hello, world with color!\n", CL_CYAN);
}

void boot(void) {
	idt_init();
	clear_screen();
	print("Echo booted.\n");
	main();
}

