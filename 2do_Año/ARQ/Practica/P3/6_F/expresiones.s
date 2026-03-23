.global main
main:

# a)
    movl $1, %eax
    sall $31, %eax

    cmpl $0x80000000, %eax
#######################################

# b)
    movl $1, %ebx
    sall $15, %ebx

    orl %ebx, %eax

    cmpl $0x80008000, %eax
#######################################

# c)
    movl $-1, %eax
    andl $0xffffff00, %eax

    cmpl $0xffffff00, %eax
#######################################

# d)
    movl $0xaa, %eax
    sall $24, %eax
    orl $0xaa, %eax

    cmpl $0xaa0000aa, %eax
#######################################

# e)
    movl $5, %eax
    sall $8, %eax

    cmpl $0x500, %eax
#######################################

# f)
    movl $1, %eax
    sall $8, %eax
    notl %eax
    andl $-1, %eax

    cmpl $0xfffffeff, %eax
#######################################

# g)
    movl $0, %eax
    subl $1, %eax

    cmpl $0xffffffff, %eax
#######################################

# h)
    movl $0x80000000, %eax
    addl $0x80000000, %eax

    cmpl $0, %eax
#######################################

    ret



















