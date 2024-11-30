#include "../sys/display.h"
#include "../sys/keyboard.h"
#include "../lib.h"
#include "../kernel/kernel.cpp"
extern "C" namespace bootloader {
    void boot(void) {
        if (!keyboard::idt_init()) {
            display::print("Failed to initialize IDT\n");
            return;
        }
        display::clear_screen();
        display::print("Echo booted.\n");
        kernel::kernel_main();
        
    }
}