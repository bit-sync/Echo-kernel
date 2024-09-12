#include "../include/io.h"
#include "../main.c"

void boot(void) {
	idt_init();
	clear_screen();
	print("Echo booted.\n");
	main();
}

