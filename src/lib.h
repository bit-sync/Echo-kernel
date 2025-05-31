#ifndef LIB_H
#define LIB_H

#include "types.h"
#include "sys/keyboard.h"
#include "sys/display.h"


namespace lib {
    // Time functions
    void sleep(uint32_t milliseconds);
    void halt(void);
    // String functions
    size_t strlen(const char* str);
    int strcmp(const char* str1, const char* str2);
    char* strcpy(char* dest, const char* src);
    char* strncpy(char* dest, const char* src, size_t n);
    char* strcat(char* dest, const char* src);
    char* strncat(char* dest, const char* src, size_t n);
    const char* strchr(const char* str, int ch);
    int strncmp(const char* s1, const char* s2, size_t n);
    // Split a string by spaces into tokens
    size_t split(const char* str, char** tokens, size_t max_tokens);
    
    // Memory functions
    void* memcpy(void* dest, const void* src, size_t n);
    void* memset(void* ptr, int value, size_t n);
    int memcmp(const void* ptr1, const void* ptr2, size_t n);
    
    // Conversion functions
    int atoi(const char* str);
    char* itoa(int value, char* str, int base);
    
    // Character functions
    bool isdigit(char c);
    bool isalpha(char c);
    bool isalnum(char c);
    bool islower(char c);
    bool isupper(char c);
    char tolower(char c);
    char toupper(char c);
    
    // Minimal sscanf: supports "%15s = %d" pattern only
    int mini_sscanf(const char* str, const char* fmt, char* out_str, int* out_int);
}

#endif // LIB_H
