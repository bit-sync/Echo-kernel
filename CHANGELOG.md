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
