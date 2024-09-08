#include <stdio.h>
#include <stdlib.h>


int main() {
    if (system("bash scripts/build.sh") == 1) {
        printf("Build failed.\n");
        return 1;
    }
}