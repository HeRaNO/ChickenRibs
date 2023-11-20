global _start

section .text

_start:
    jmp MESSAGE

GOBACK:
    mov rax, 0x01
    mov rdi, 0x01
    pop rsi
    mov rdx, 0x0A
    syscall

    mov rax, 0xE7
    xor rdi, rdi
    syscall

MESSAGE:
    call GOBACK
    db "Hi, CNSS!", 0ah
