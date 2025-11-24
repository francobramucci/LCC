.global fact2

fact2:
    movq %rdi, %rcx
    movq $1, %rax
    cmpq $1, %rcx
    jb fin

for:
    mulq %rcx
    loop for

fin: 
    ret
