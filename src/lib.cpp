#include "lib.h"
#include "types.h"

namespace lib {
    // Time functions
    static inline uint64_t rdtsc() {
        uint32_t low, high;
        asm volatile("rdtsc" : "=a"(low), "=d"(high));
        return ((uint64_t)high << 32) | low;
    }

    void sleep(uint32_t milliseconds) {
        // Estimate CPU frequency (assuming ~2GHz)
        const uint64_t cycles_per_ms = 2000000; // 2 million cycles per millisecond
        uint64_t start = rdtsc();
        uint64_t end = start + (cycles_per_ms * milliseconds);
        
        // Busy wait until we reach the target cycle count
        while (rdtsc() < end) {
            // Add a small delay to prevent overwhelming the CPU
            for(volatile int i = 0; i < 100; i++) {}
        }
    }

    // String functions
    size_t strlen(const char* str) {
        size_t len = 0;
        while (str[len] != '\0') {
            len++;
        }
        return len;
    }

    int strcmp(const char* str1, const char* str2) {
        while (*str1 && (*str1 == *str2)) {
            str1++;
            str2++;
        }
        return *(unsigned char*)str1 - *(unsigned char*)str2;
    }

    char* strcpy(char* dest, const char* src) {
        char* original_dest = dest;
        while ((*dest++ = *src++) != '\0');
        return original_dest;
    }

    char* strncpy(char* dest, const char* src, size_t n) {
        size_t i;
        for (i = 0; i < n && src[i] != '\0'; i++) {
            dest[i] = src[i];
        }
        for (; i < n; i++) {
            dest[i] = '\0';
        }
        return dest;
    }

    char* strcat(char* dest, const char* src) {
        char* original_dest = dest;
        while (*dest) dest++;
        while ((*dest++ = *src++) != '\0');
        return original_dest;
    }

    char* strncat(char* dest, const char* src, size_t n) {
        char* original_dest = dest;
        while (*dest) dest++;
        size_t i;
        for (i = 0; i < n && src[i] != '\0'; i++) {
            dest[i] = src[i];
        }
        dest[i] = '\0';
        return original_dest;
    }

    const char* strchr(const char* str, int ch) {
        while (*str != '\0') {
            if (*str == ch) {
                return str;
            }
            str++;
        }
        return nullptr;
    }
    void halt(void) {
        asm volatile("hlt");
    }

    // Memory functions
    void* memcpy(void* dest, const void* src, size_t n) {
        char* d = (char*)dest;
        const char* s = (const char*)src;
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
        return dest;
    }

    void* memset(void* ptr, int value, size_t n) {
        unsigned char* p = (unsigned char*)ptr;
        for (size_t i = 0; i < n; i++) {
            p[i] = (unsigned char)value;
        }
        return ptr;
    }

    int memcmp(const void* ptr1, const void* ptr2, size_t n) {
        const unsigned char* p1 = (const unsigned char*)ptr1;
        const unsigned char* p2 = (const unsigned char*)ptr2;
        for (size_t i = 0; i < n; i++) {
            if (p1[i] != p2[i]) {
                return p1[i] - p2[i];
            }
        }
        return 0;
    }

    // Conversion functions
    int atoi(const char* str) {
        int result = 0;
        int sign = 1;
        
        // Skip whitespace
        while (*str == ' ') str++;
        
        // Handle sign
        if (*str == '-') {
            sign = -1;
            str++;
        } else if (*str == '+') {
            str++;
        }
        
        // Convert digits
        while (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str - '0');
            str++;
        }
        
        return sign * result;
    }

    char* itoa(int value, char* str, int base) {
        if (base < 2 || base > 36) {
            *str = '\0';
            return str;
        }
        
        char* ptr = str;
        bool negative = false;
        
        if (value < 0) {
            negative = true;
            value = -value;
        }
        
        do {
            int digit = value % base;
            *ptr++ = digit < 10 ? '0' + digit : 'a' + digit - 10;
            value /= base;
        } while (value);
        
        if (negative) {
            *ptr++ = '-';
        }
        
        *ptr = '\0';
        
        // Reverse the string
        char* start = str;
        ptr--;
        while (start < ptr) {
            char temp = *start;
            *start = *ptr;
            *ptr = temp;
            start++;
            ptr--;
        }
        
        return str;
    }

    // Character functions
    bool isdigit(char c) {
        return c >= '0' && c <= '9';
    }

    bool isalpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool isalnum(char c) {
        return isdigit(c) || isalpha(c);
    }

    bool islower(char c) {
        return c >= 'a' && c <= 'z';
    }

    bool isupper(char c) {
        return c >= 'A' && c <= 'Z';
    }

    char tolower(char c) {
        return isupper(c) ? c + ('a' - 'A') : c;
    }

    char toupper(char c) {
        return islower(c) ? c - ('a' - 'A') : c;
    }
}
