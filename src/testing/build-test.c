#include <stdio.h>
#include <stdlib.h>


int main() {
    if (system("nasm -f elf32 kernel.asm -o tmp/kasm.o") == 1) {
        printf("Assembly failed.\n");
        return 1;
    }
    if (system("gcc -m32 -c kernel.c -o tmp/kc.o") == 1) {
        printf("Compilation failed.\n");
        return 1;
    } 
    if (system("ld -m elf_i386 -T link.ld -o kernel tmp/kasm.o tmp/kc.o") == 1) {
        printf("Linking failed.\n");
        return 1;
    }
    printf("Build and test successful.\n");
}