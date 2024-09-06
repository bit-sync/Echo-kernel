set -e

cd ~/Echo-kernel/src

nasm -f elf32 boot/boot.asm -o tmp/bootkc.o

gcc -m32 -c boot/boot.c -o tmp/kc.o

ld -m elf_i386 -T link.ld -o ec-kernel tmp/bootkc.o tmp/kc.o
