#include "../lib.h"

using namespace lib;

extern "C" namespace kernel {
    void kernel_main(void) {
        display::clear_screen();
        display::print("Hello World!\n");
        sleep(5000); // Sleep for 1 second
        display::print("Goodbye World!\n");
        halt();
        display::print("This should not print :)");
    }
} 