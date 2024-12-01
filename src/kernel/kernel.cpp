#include "../sys/display.h"
#include "../sys/keyboard.h"
#include "../sys/ports.h"
#include "../lib.h"

using namespace lib;
using namespace display;
using namespace ports;

namespace kernel {
    // Forward declarations
    namespace eshell {
        void loop(void);
        void start_eshell(void);
    }

    void sleep(int ms) {
        for(int i = 0; i < ms * 100000; i++) {
            asm volatile("nop");
        }
    }

    void shutdown() {
        printc("\nShutting down...\n", display::CL_LIGHT_RED);
        
        // Try ACPI shutdown first
        outw(QEMU_SHUTDOWN_PORT, 0x2000);  // QEMU-specific shutdown
        
        // Try APM shutdown
        outw(APM_SHUTDOWN_PORT, 0x2000);   // APM shutdown
        
        // Try standard ACPI shutdown
        outw(ACPI_SHUTDOWN_PORT, 0x3400);
        
        // If we get here, try legacy keyboard controller method
        for(int i = 0; i < 10; i++) {
            outb(KBC_RESET_PORT, 0xFE);  // Send reset command to keyboard controller
            sleep(100);
        }
        
        // If all else fails, halt the CPU
        printc("Failed to shutdown. Halting CPU...\n", display::CL_LIGHT_RED);
        asm volatile("cli");  // Disable interrupts
        while(1) {
            asm volatile("hlt");
        }
    }

    void main(void) {
        #ifdef DEBUG
            printc("[DEBUG] Kernel main starting\n", display::CL_LIGHT_CYAN);
        #endif

        clear_screen();
        
        // Start shell in main process
        #ifdef DEBUG
            printc("[DEBUG] Starting Eshell\n", display::CL_LIGHT_CYAN);
        #endif
        eshell::start_eshell();
    }

    namespace eshell {
        void start_eshell(void) {
            printc("Welcome to Eshell\nBuilt on the Echo Kernel\n", display::CL_LIGHT_GREEN);
            while (1) {
                loop();
            }
        }

        void loop(void) {
            char* input;
            printc("user@system:$ ", display::CL_RED);
            printc("> ", display::CL_LIGHT_BLUE);
            input = keyboard::get_input("");
            
            if (strcmp(input, "clear") == 0) {
                clear_screen();
            }
            else if (strcmp(input, "shutdown") == 0) {
                printc("Shutting down...\n", display::CL_LIGHT_RED);
                shutdown();
            }
            else if (strcmp(input, "help") == 0) {
                printc("clear - clear the screen\n", display::CL_LIGHT_BLUE);
                printc("shutdown - shutdown the system\n", display::CL_LIGHT_BLUE);
                printc("help - display this help message\n", display::CL_LIGHT_BLUE);
            }
            else {
                printc("Unknown command: ", display::CL_LIGHT_BLUE);
                print(input);
            }
            print_newline();
        }
    }
}