.data
a: .word -1
b: .byte 0xaa, 99
c: .float 1.5
str: .asciz "Hola mundo\n"

.text
.global main

main:
    leaq a, %rdx
    movw (%rdx), %ax
    movb 3(%rdx), %al
    movl 8(%rdx), %esi
    movl 4(%rdx), %edi
    movl %esi, (%rdx)
    ret
