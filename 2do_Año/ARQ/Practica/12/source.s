.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10
str: .asciz "Promedio: %d\nMaximo: %d\nMinimo: %d\n"

.text
.global main

main:
    leaq list, %rdi                 # Arg 1
    movzbq length, %rsi             # Arg 2
    call promedio_array
    movq %rax, %r8
    
    leaq list, %rdi                 # Arg 1
    movzbq length, %rsi             # Arg 2
    call maximo_array
    movq %rax, %r9
    
    leaq list, %rdi                 # Arg 1
    movzbq length, %rsi             # Arg 2
    call minimo_array
    movq %rax, %r10

    leaq str, %rdi
    movq %r8, %rsi
    movq %r9, %rdx
    movq %r10, %rcx
    movq $0, %rax
    call printf

    ret

sumar_array:
    movq %rsi, %rcx
    xorq %rax, %rax

.suma_loop:
    addl -4(%rdi, %rcx, 4), %eax
    loop .suma_loop

    ret

promedio_array:
    pushq %rsi
    call sumar_array
    
    popq %rcx
    cqto
    idiv %rcx

    ret

maximo_array:
    xorq %rax, %rax
    movq %rsi, %rcx

    movl -4(%rdi, %rcx, 4), %eax
    decq %rcx

for:
    cmpl -4(%rdi, %rcx, 4), %eax
    jl menor
    jmp seguir

menor:
    movl -4(%rdi, %rcx, 4), %eax

seguir:
    loop for

    ret

minimo_array:
    xorq %rax, %rax
    movq %rsi, %rcx

    movl -4(%rdi, %rcx, 4), %eax
    decq %rcx

for1:
    cmpl -4(%rdi, %rcx, 4), %eax
    jg mayor
    jmp seguir1

mayor:
    movl -4(%rdi, %rcx, 4), %eax

seguir1:
    loop for1

    ret

    
    




