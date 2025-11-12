.data
str: .asciz "La suma es %d\n"

.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp

    movq %rdi, %r12
    movq %rsi, %rbx
    xorl %r13d, %r13d
    movl $1, %r14d

bucle:
    cmp %r12, %r14
    jge fin
    movq (%rbx, %r14, 8), %rdi
    call atoi
    addq %rax, %r13
    incq %r14
    jmp bucle

fin:
    leaq str, %rdi
    movq %r13, %rsi
    xorl %eax, %eax
    call printf

    movq %rbp, %rsp
    popq %rbp
    xorl %eax, %eax
    ret
