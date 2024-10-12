all: build

ECHO_VERSION ="0.1.5_Alpha"

build:
	@mkdir tmp
	@echo building...
	@echo Installing dependancies
	@sudo apt install nasm git gcc -y
	@echo done
	@nasm -f elf32 src/boot/boot.asm -o tmp/kasm.o
	@gcc -fno-stack-protector -m32 -c src/boot/boot.c -o tmp/kc.o
	@ld -m elf_i386 -T link.ld -o kernel tmp/kasm.o tmp/kc.o
	@rm -rf tmp
	@echo done

iso:
	@echo building iso...
	
	@mkdir -p iso/boot/grub
	@make build
	@cp kernel iso/boot
	@cp grub-config/grub.cfg iso/boot/grub 
	@grub-mkrescue -o Echo-kernel-$(ECHO_VERSION).iso
	@grub-mkrescue -o Echo-kernel-$(ECHO_VERSION).iso iso
	@rm -rf iso
	@echo done

vm-test:
	@qemu-system-i386 -kernel kernel

clean:
	@rm -rf tmp
	@rm kernel