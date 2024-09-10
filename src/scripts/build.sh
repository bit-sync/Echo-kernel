echo building...

echo Installing dependancies

sudo apt install nasm git gcc -y

echo done

export ECHO_VERSION="0.0.2"
nasm -f elf32 boot/boot.asm -o tmp/kasm.o
gcc -fno-stack-protector -m32 -c boot/boot.c -o tmp/kc.o
ld -m elf_i386 -T link.ld -o kernel tmp/kasm.o tmp/kc.o
echo done