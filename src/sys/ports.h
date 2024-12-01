#ifndef PORTS_H
#define PORTS_H

#include "../types.h"

namespace ports {
    // Port I/O functions
    static inline void outb(uint16_t port, uint8_t value) {
        asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
    }

    static inline uint8_t inb(uint16_t port) {
        uint8_t ret;
        asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
        return ret;
    }

    static inline void outw(uint16_t port, uint16_t value) {
        asm volatile("outw %0, %1" : : "a"(value), "Nd"(port));
    }

    static inline uint16_t inw(uint16_t port) {
        uint16_t ret;
        asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
        return ret;
    }

    // ACPI shutdown port addresses
    static constexpr uint16_t QEMU_SHUTDOWN_PORT = 0xB004;
    static constexpr uint16_t APM_SHUTDOWN_PORT = 0x604;
    static constexpr uint16_t ACPI_SHUTDOWN_PORT = 0x4004;
    static constexpr uint16_t KBC_RESET_PORT = 0x64;
}

#endif // PORTS_H
