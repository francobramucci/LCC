.data
arr: .byte 1, 2, 3, 4, 5
length: .byte 5

.text
.global main

main:
    movzbq length, %rcx             # Almaceno el largo del array en rcx
    movq $0, %rbx                   # Inicializo el indice en 0

pushear:
    movzbq arr(, %rbx, 1), %rdx
    pushq %rdx
    incq %rbx
    loop pushear

    movzbq length, %rcx             # Almaceno el largo del array en rcx
    movq $0, %rbx                   # Inicializo el indice en 0

popear:
    popq %rax
    movb %al, arr(, %rbx, 1)
    incq %rbx
    loop popear

    ret
