.global sum

sum:
    pushq %rbp

    movl $0, %ecx

for:
    movss (%rdi, %rcx, 4), %xmm0
    movss (%rsi, %rcx, 4), %xmm1
    addss %xmm1, %xmm0
    movss %xmm0, (%rdi, %rcx, 4)
    incl %ecx
    cmpl %edx, %ecx
    jl for

    popq %rbp

    ret
