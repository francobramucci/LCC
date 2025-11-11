.text
.global main

main:
    movq $-1, %rax      # rax = 0xffffffffffffffff
    movb $0, %al        # rax = 0xffffffffffffff00
    movw $0, %ax        # rax = 0xffffffffffff0000
    movl $0, %eax       # rax = 0xffffffff00000000
    ret
