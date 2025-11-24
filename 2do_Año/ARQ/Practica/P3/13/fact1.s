.global fact1

fact1:
    cmpq $1, %rdi
    jbe retornar

    pushq %rdi

    decq %rdi
    call fact1
    
    popq %rcx
    mulq %rcx
    
    ret
retornar:
    movq $1, %rax
    ret
