# Changelog

## [1.5.0 r1] - 2024-11-30

### Added
- Interactive shell (Eshell) with command support
- System shutdown functionality (ACPI/APM)
- Port I/O utilities in `sys/ports.h`
- Colored boot messages
- Shell commands: clear, shutdown, help
- Welcome message on boot

### Changed
- Improved boot sequence with status messages
- Enhanced display color support
- Reorganized kernel initialization

### Fixed
- Double screen clear in kernel main
- Namespace conflicts with color constants

## [1.0.0 r2] - 2024-11-30

### Added
- Comprehensive documentation in Docusaurus format
- Automatic dependency installation in build process
- Python kconfiglib for kernel configuration

### Changed
- Updated kernel version to 1.0.0
- Improved build system with automatic dependency handling
- Reorganized documentation structure
- Updated project README with clearer instructions
- Simplified kernel configuration options

### Removed
- HELLO_WORLD configuration option
- Redundant version information

### Build System
- Added automatic installation of build dependencies
- Added pip installation of kconfiglib for menuconfig
- Streamlined build process with better error handling

### Documentation
- Added comprehensive API reference
- Added detailed component documentation:
  - Display system
  - Keyboard system
  - Bootloader
  - Standard library
- Improved README with:
  - Clear project description
  - Updated build instructions
  - System requirements
  - Project structure

### Technical Details
- Base Components:
  - Text-mode display (80x25)
  - Interrupt-driven keyboard (US QWERTY)
  - Basic bootloader
  - Standard library utilities
- Build Requirements:
  - GCC (i686)
  - NASM
  - GRUB
  - Make
  - Python (for kconfiglib)

### Configuration
- Simplified Kconfig options
- Focused on essential build configurations
- Removed experimental features