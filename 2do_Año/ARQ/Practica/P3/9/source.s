.data
a: .word -1
b: .byte 0xaa, 99
c: .float 1.5
str: .asciz "Hola mundo\n"

.text
.global main

main:
    leaq a, %rdx
    movw (%rdx), %ax    # ax = 0xffff
    movb 3(%rdx), %al   # al = 0x63
    movl 8(%rdx), %esi  # esi = "aloH"
    movl 4(%rdx), %edi  # edi = 0x3fc00000
    movl %esi, (%rdx)
    ret

#   Etiqueta      Dirección de memoria       Valor almacenado
#   a             0x404010                   0xffff
#   b             0x404012                   0xaa
#                 0x404013                   0x63
#   c             0x404014                   1.5
#   str           0x404018                   'H'
#                 0x404019                   'o'
#                 0x40401A                   'l'
#                 0x40401B                   'a'
#                 0x40401C                   ' '
#                 0x40401D                   'm'
#                 0x40401E                   'u' 
#                 0x40401F                   'n'
#                 0x404020                   'd'
#                 0x404021                   'o'
#                 0x404022                   '\n'
#                 0x404023                   '0'





