bits 64


default rel

_start:
lea r14, [rel _shellcode+0x12345678]
sub r14, 0x12345678

push byte 23                        ; put amount of bytes to decode
pop rcx                             ; in rcx

_decode:
dec byte [r14]
add r14, 1
loop _decode

_shellcode:                         ; place 'encoded' shellcode here
