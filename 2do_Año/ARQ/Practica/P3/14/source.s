# suma: [int] -> int
.data
str: .asciz "Cantidad de argumentos ingresados: %d. La suma es %d.\n"

.text
.global main

main:
    pushq %rbp
    movq %rsp, %rbp

    # %rdi -> argc, %rsi -> argv[]
    # rdi la cantidad de argumentos (int).
    # rsi es un arreglo de direcciones a esos argumentos.
    # Siempre el primer argumento es el nombre del programa.

    movl %edi, %r12d    # r12d -> cant. de argumentos
    decl %r12d          # restamos uno por el nombre del programa.
    movq %rsi, %rbx     # rbx -> dirección de los elementos
    xorl %r13d, %r13d   # r13d -> resultado acumulado
    movl $1, %r14d      # r14d -> contador

bucle:
    cmpl %r12d, %r14d
    jg fin
    movq (%rbx, %r14, 8), %rdi
    call atoi
    imull %eax
    addl %eax, %r13d
    incl %r14d
    jmp bucle

fin:
    leaq str, %rdi
    movl %r12d, %esi
    movl %r13d, %edx
    xorl %eax, %eax
    call printf

    movq %rbp, %rsp
    popq %rbp
    xorl %eax, %eax
    ret
