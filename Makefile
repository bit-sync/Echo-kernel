# Check if we're running 'make menuconfig'
ifneq ($(MAKECMDGOALS), menuconfig)
    # If .config is missing, prompt the user to run menuconfig
    ifeq ($(wildcard .config),)
        $(error ".config file not found! Please run 'make menuconfig' to create it.")
    endif
endif

# Load .config settings if the file exists
-include .config

all: check_build

check_build:
	@if [ "$(CONFIG_BUILD_ISO)" = "y" ]; then \
		$(MAKE) iso; \
	else \
		$(MAKE) build; \
	fi

ECHO_VERSION = "0.1.5_Alpha"

build:
	@mkdir -p tmp
	@echo building...
	@echo Installing dependencies...
	@sudo apt install nasm git gcc -y
	@echo done
	@nasm -f elf32 src/boot/boot.asm -o tmp/kasm.o
	@gcc -fno-stack-protector -m32 -c src/boot/boot.c -o tmp/kc.o
	@ld -m elf_i386 -T link.ld -o ecImage tmp/kasm.o tmp/kc.o
	@rm -rf tmp
	@echo done

iso:
	@echo building iso...
	@mkdir -p iso/boot/grub
	@$(MAKE) build
	@cp ecImage iso/boot
	@cp grub-config/grub.cfg iso/boot/grub 
	@grub-mkrescue -o "Echo-kernel-$(CONFIG_VERSION)-$(CONFIG_SUBVERSION).iso" iso
	@rm -rf iso
	@echo done

vm-test:
	@qemu-system-i386 -kernel ecImage

clean:
	@rm -rf tmp
	@rm -f ecImage

menuconfig:
	@menuconfig
