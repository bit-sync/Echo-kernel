#include "include/stdio.h"


void boot(void)
{
	idt_init();
	kb_init();
	clear_screen();
	printc("test", DPCL_RED);
	while(1);
}