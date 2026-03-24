.data
a: .long 0x7fffffff
b: .long 1
msg1: .asciz "Ejecutando foo1...\n"
msg2: .asciz "Ejecutando foo2...\n"
format: .asciz "0x%x\n"
format1: .asciz "0x%x 0x%x\n"

.text
.global main
main:
    push %rbp
    movq %rsp, %rbp
    
    call foo2

    pushq %rax

    call foo1

    pushq %rax

    leaq format1, %rdi
    popq %rsi
    popq %rdx
    xorl %eax, %eax
    call printf

    leave
    ret

foo1:
    leaq msg1, %rdi
    xorl %eax, %eax
    call printf
    
    leaq format, %rdi
    movl b, %esi
    sall $31, %esi
    leaq a, %rcx
    addl %esi, (%rcx) 

    movl (%rcx), %esi

    xorl %eax, %eax
    call printf

    leaq a, %rcx
    movl (%rcx), %eax

    ret

 foo2:
    leaq msg2, %rdi
    xorl %eax, %eax
    call printf
    
    movl b, %esi
    leaq a, %rcx
    addl %esi, (%rcx) 

    leaq format, %rdi
    movl (%rcx), %esi
    xorl %eax, %eax
    call printf

    leaq a, %rcx
    movl (%rcx), %eax

    ret
   
    
