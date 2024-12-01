# Echo Kernel

A minimalist kernel written in Assembly and C++, designed for educational purposes and system programming learning.

## Features

- Text-mode display with color support (80x25)
- Interrupt-driven keyboard input (US QWERTY)
- Basic bootloader implementation
- Standard library with common utilities
- Configurable kernel options
- Interactive shell (Eshell) with command support
- Power management (ACPI/APM shutdown support)

## Shell Commands

Echo Kernel comes with an interactive shell (Eshell) that supports the following commands:

- `clear` - Clear the screen
- `shutdown` - Safely shutdown the system
- `help` - Display available commands

## Building

### Prerequisites
These will be installed automatically if not already present:
- GCC cross-compiler for i686
- NASM assembler
- GRUB bootloader
- make

### Configuration

The kernel can be configured using `make menuconfig`. Available options:



### Build Commands

```bash
# Configure the kernel
make menuconfig

# Build the kernel
make

# Create bootable image
make iso
```

## System Requirements

- x86 compatible processor
- At least 32MB RAM
- VGA-compatible display
- PS/2 keyboard
- ACPI or APM support (for shutdown functionality)

## Documentation

Comprehensive documentation is available in the `/docs` directory:
- `display.md` - Display subsystem documentation
- `eshell.md` - Shell interface documentation

## Project Structure

```
Echo-kernel/
├── src/
│   ├── bootloader/    # Boot sequence implementation
│   ├── kernel/        # Core kernel code
│   ├── sys/          # System interfaces
│   │   ├── display/  # Screen output
│   │   └── keyboard/ # Input handling
│   └── lib/          # Standard library
├── docs/             # Documentation
└── grub-config/      # GRUB bootloader configuration
```

## Contributing

Contributions are welcome! Please read our contributing guidelines before submitting pull requests.

## License

This project is licensed under the terms found in the LICENSE file.
