#include "../include/io.h"

void boot(void) {
	idt_init();
	clear_screen();
	print("Echo booted.\n");
	main();
}

void main(void) {
	print("Hello, world!\n");
	printc("Hello, world with color!\n", CL_CYAN);
}
 







