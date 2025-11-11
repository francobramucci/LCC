.global main

main:
    # a) 0x80000000
    movl $1, %eax
    sall $31, %eax
    
    # b) 0x80008000
    movl $1, %eax
    sall $31, %eax

    movw $1, %bx
    salw $15, %bx
    orw %bx, %ax
    
    # c) 0xffffff00
    movl $-1, %eax
    andl $0xffffff00, %eax

    # d) 0xaa0000aa
    movl $0xAA, %eax
    sall $24, %eax
    orb $0xAA, %al

    # e) 0x00000500
    movl $5, %eax
    sall $8, %eax

    # f) 0xfffffeff
    movl $1, %eax
    sall $8, %eax
    negl %eax
    andl $-1, %eax
    
    # g) 0xffffffff
    movl $0, %eax
    subl $1, %eax 
    
    # h) 0x00000000
    movl $0x80000000, %eax
    addl $-0x80000000, %eax

    ret

# b) es necesario usar GDB ya que el código de salida devuelve como entero el
# valor de los 8 bits menos significativos de rax. En este caso necesitamos los
# 32 bits menos significativos.
