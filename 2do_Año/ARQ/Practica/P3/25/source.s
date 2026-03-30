.global sum_simd

sum_simd:
    pushq %rbp

    movl $0, %ecx

for:
    cmpl $4, %edx
    jl menor

    movups (%rdi, %rcx, 8), %xmm0
    movups (%rsi, %rcx, 8), %xmm1
    
    addps %xmm1, %xmm0

    movups %xmm0, (%rdi, %rcx, 8)

    subl $4, %edx
    addl $2, %ecx

    jmp for

menor:
    cmpl $0, %edx
    jz fin
    leaq (%rdi, %rcx, 8), %rdi
    leaq (%rsi, %rcx, 8), %rsi
    movl $0, %ecx

for1:
    movss (%rdi, %rcx, 4), %xmm0
    movss (%rsi, %rcx, 4), %xmm1

    addss %xmm1, %xmm0
    movss %xmm0, (%rdi, %rcx, 4)
    
    incl %ecx
    decl %edx
    jz fin
    jmp for1

fin:
    popq %rbp
    ret

    
