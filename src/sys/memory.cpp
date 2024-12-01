#include "../lib.h"

// Simple memory allocator for kernel heap
static char kernel_heap[1024 * 1024]; // 1MB heap
static unsigned int heap_ptr = 0;

void* operator new(unsigned int size) throw() {
    if (heap_ptr + size > sizeof(kernel_heap)) {
        return 0; // Out of memory
    }
    void* ptr = &kernel_heap[heap_ptr];
    heap_ptr += size;
    return ptr;
}

void* operator new[](unsigned int size) throw() {
    return operator new(size);
}

void operator delete(void* ptr) throw() {
    // In this simple implementation, we don't actually free memory
    // A proper implementation would need a memory manager
    (void)ptr;
}

void operator delete[](void* ptr) throw() {
    operator delete(ptr);
}

void operator delete(void* ptr, unsigned int size) throw() {
    (void)ptr;
    (void)size;
}

void operator delete[](void* ptr, unsigned int size) throw() {
    operator delete(ptr, size);
}
