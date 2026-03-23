.data
format: .asciz "%ld\n"
format1: .asciz "%lu"
i : .quad 0xdeadbeef

.text
.global main
main:
    movq $format, %rdi      # El primer argumento es el formato
    movq $1234, %rsi        # El valor a imprimir
    xorl %eax, %eax         # Cantidad de valores de punto flotante
    call printf

# a)
    leaq format1, %rdi
    movq %rsp, %rsi
    xorl %eax, %eax
    call printf
    
# b
