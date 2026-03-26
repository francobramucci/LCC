.data
str1: .asciz "La cantidad de argumentos es insuficiente\n"
str2: .asciz "Cantidad de argumentos: %d, suma de los argumentos %d\n"

.text
.global main
main:
    pushq %rbp
    movq %rsp, %rbp

    cmpl $2, %edi
    jge enough_args
    
    leaq str1, %rdi
    xorl %eax, %eax
    call printf
    
    jmp epilogo

enough_args:
# En vez de almacenar variables locales en la pila
# Preservamos los registros calle saved que utilizaremos
    pushq %rbx      # %rbx -> acumulador
    pushq %r12      # %r12 -> argc
    pushq %r13      # %r13 -> argv
    pushq %r14      # %r13 -> contador

    movl $0, %ebx
    movl %edi, %r12d
    movq %rsi, %r13
    movl $1, %r14d

for:
    movq (%r13, %r14, 8), %rdi
    call atoi
    addl %eax, %ebx
    
    incl %r14d
    cmpl %r12d, %r14d
    jl for
    #
    
    leaq str2, %rdi
    movl %r12d, %esi
    movl %ebx, %edx
    xorl %eax, %eax
    call printf

# Recuperamos los valores anteriores de los registros
    popq %r14       
    popq %r13
    popq %r12
    popq %rbx

epilogo:
    movq %rbp, %rsp
    popq %rbp

    xorl %eax, %eax
    ret
    
