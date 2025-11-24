.global main

main:

    # Solo para este tamaño el mov pone en 0 la parte alta del registro.
    movl $-1, %eax      # rax = 0x00000000ffffffff
    movl $2, %ecx       # rcx = 0x0000000000000002 
    imull %ecx          # rdx = 0x00000000ffffffff, rax = 0x00000000ffffffffe

    # Completar para que el resultado correcto como signed quede en rax
    rolq $32, %rdx      # rdx = 0xffffffff00000000
    addq %rdx, %rax     # rax = 0xfffffffffffffffe
    #

    xorq %rax, %rax     # eax = 0x0
    movw $-1, %ax       # eax = 0x0000ffff
    movw $2, %cx        # ecx = 0x00000002
    mulw %cx            # edx = 0x00000001, eax = 0x0000fffe

    # Completar para que el resultado correcto como unsigned int quede en eax
    roll $16, %edx      # edx = 0x00010000
    addl %edx, %eax     # eax = 0x0001fffe
    #

    ret
