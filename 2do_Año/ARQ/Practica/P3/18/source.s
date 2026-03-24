.global calculo
calculo:
    pushq %rbp
    movq %rsp, %rbp

    movzbl %dil, %r10d
    movzbl %dl, %r11d
    addl %r11d, %r10d
    addl %ecx, %r10d

    movl 16(%rbp), %eax
    addl 24(%rbp), %eax

    imull %r10d

    movq %rbp, %rsp
    popq %rbp
    ret
    
