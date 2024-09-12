#include "include/io.h"

int main() {
    print("Hello\n");
    printc("Hello with color\n", CL_MAGENTA);
    kb_init();
    while (1);
}
   
