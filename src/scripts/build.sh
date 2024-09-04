cd ~/Echo-kernel/src

nasm -f elf32 boot.asm -o tmp/kasm.o

gcc -m32 -c boot.c -o tmp/kc.o

ld -m elf_i386 -T link.ld -o ec-kernel.iso tmp/kasm.o tmp/kc.o
