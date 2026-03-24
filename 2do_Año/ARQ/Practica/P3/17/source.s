.data
format: .asciz "%ld\n"
format1: .asciz "%lx\n"
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
    
# b y c)
    leaq format1, %rdi
    movq $format, %rsi
    xorl %eax, %eax
    call printf

# d)
    leaq format1, %rdi
    movq (%rsp), %rsi
    xorl %eax, %eax
    call printf

# e)
    leaq format1, %rdi
    movq 8(%rsp), %rsi
    xorl %eax, %eax
    call printf

# f)
    leaq format, %rdi
    movq i, %rsi
    xorl %eax, %eax
    call printf

# g)
    leaq format1, %rdi
    movq $i, %rsi
    xorl %eax, %eax
    call printf

    ret 
