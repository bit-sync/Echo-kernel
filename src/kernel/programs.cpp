#include "../sys/display.h"
#include "../sys/keyboard.h"
#include "../sys/ports.h"
#include "../lib.h"



using namespace lib;
using namespace display;
using namespace ports;

// Simple addition program: adds two integers and prints the result
void addition_program(int a, int b) {
    int sum = a + b;
    char buffer[32];
    lib::itoa(sum, buffer, 10);
    display::printc(buffer, display::CL_LIGHT_GREEN);
    display::printc("\n", display::CL_LIGHT_GREEN);
}