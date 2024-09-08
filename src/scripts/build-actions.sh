nasm -f elf32 kernel.asm -o tmp/kasm.o

gcc -fno-stack-protector -m32 -c kernel.c -o tmp/kc.o

ld -m elf_i386 -T link.ld -o kernel tmp/kasm.o tmp/kc.o