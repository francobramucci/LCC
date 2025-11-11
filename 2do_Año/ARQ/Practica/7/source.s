.global main

main:
    # Permutar mitad alta y baja
    rolq $32, %rax
    
    #
    movq $64, %rcx
    movq $0, %rbx

rotar:
    rolq $1, %rax
    addq
    ret
