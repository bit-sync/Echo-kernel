; keyboard.asm
; Contains assembly code for keyboard handling

global keyboard_handler
global read_port
global write_port
global load_idt

extern keyboard_handler_main  ; Add external reference to the C++ function

; keyboard_handler
keyboard_handler:
    pushad
    cld
    call    keyboard_handler_main
    popad
    iret

; read_port - Read a byte from an I/O port
; Parameters:
;   port (on stack) - The I/O port to read from
read_port:
    mov     edx, [esp + 4]    ; Get the port parameter
    in      al, dx            ; Read a byte from the port
    ret

; write_port - Write a byte to an I/O port
; Parameters:
;   port (on stack) - The I/O port to write to
;   data (on stack) - The byte to write
write_port:
    mov     edx, [esp + 4]    ; Get the port parameter
    mov     al, [esp + 8]     ; Get the data parameter
    out     dx, al            ; Write the byte to the port
    ret

; load_idt - Load the Interrupt Descriptor Table
; Parameters:
;   idt_ptr (on stack) - Pointer to the IDT descriptor
load_idt:
    mov     edx, [esp + 4]    ; Get the IDT descriptor pointer
    lidt    [edx]             ; Load the IDT
    sti                       ; Enable interrupts
    ret
