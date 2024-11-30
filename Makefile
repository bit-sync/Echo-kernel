# Check if we're running 'make menuconfig'
ifneq ($(MAKECMDGOALS), menuconfig)
    # If .config is missing, prompt the user to run menuconfig
    ifeq ($(wildcard .config),)
        $(error ".config file not found! Please run 'make menuconfig' to create it.")
    endif
endif

# Load .config settings if the file exists
-include .config

ifeq ($(CONFIG_HELLO_WORLD),y)
	CFLAGS += -DHELLO_WORLD
endif

all: check_build

check_build:
	@if [ "$(CONFIG_BUILD_ISO)" = "y" ]; then \
		$(MAKE) iso; \
	else \
		$(MAKE) build; \
	fi


build:
	@mkdir -p tmp
	@echo building...
	@echo Installing dependencies...
	@sudo apt install nasm git gcc grub-common xorriso -y
	@echo done
	@nasm -f elf32 src/bootloader/boot.asm -o tmp/kasm.o
	@nasm -f elf32 src/drivers/keyboard.asm -o tmp/keyboard_asm.o
	@g++ $(CFLAGS) -fno-stack-protector -m32 -c src/bootloader/boot.cpp -o tmp/kc.o
	@g++ $(CFLAGS) -fno-stack-protector -m32 -c src/sys/keyboard.cpp -o tmp/kkeyboard.o
	@g++ $(CFLAGS) -fno-stack-protector -m32 -c src/sys/display.cpp -o tmp/kdisplay.o
	@g++ $(CFLAGS) -fno-stack-protector -m32 -c src/lib.cpp -o tmp/klib.o
	@ld -m elf_i386 -T link.ld -o ecImage tmp/kasm.o tmp/keyboard_asm.o tmp/kc.o tmp/kkeyboard.o tmp/kdisplay.o tmp/klib.o
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
	@pip install kconfiglib
	@menuconfig
