#include "../sys/display.h"
#include "../sys/keyboard.h"
#include "../lib.h"
#include "../kernel/kernel.cpp"
extern "C" namespace bootloader {
    void boot(void) {
        #ifdef DEBUG
            display::printc("[DEBUG] Starting boot process...\n", display::CL_LIGHT_CYAN);
        #endif
        display::clear_screen();
        display::printc("Booting...\n", display::CL_LIGHT_BLUE);
        sleep(1500);
        #ifdef DEBUG
            display::printc("[DEBUG] Initializing IDT...\n", display::CL_LIGHT_CYAN);
        #endif
        if (!keyboard::idt_init()) {
            display::printc("Failed to initialize IDT\n", display::CL_LIGHT_RED);
            return;
        }
        else {
            display::printc("IDT initialized\n", display::CL_LIGHT_GREEN);
            #ifdef DEBUG
                display::printc("[DEBUG] IDT initialized\n", display::CL_LIGHT_CYAN);
            #endif
        }
        lib::sleep(1000);
        #ifdef DEBUG
            display::printc("[DEBUG] Starting kernel main...\n", display::CL_LIGHT_CYAN);
        #endif
        kernel::main();
        
    }
}