.global main

main:
    # Valor inicial de rax
    movq $0xAA, %rax

    # Permutar mitad alta y baja
    rolq $32, %rax
    
    # Calcular bits en uno de rax
    movq $64, %rcx
    movq $0, %rbx

calcular_unos:
    rolq $1, %rax
    adcq $0, %rbx
    loop calcular_unos

    ret
