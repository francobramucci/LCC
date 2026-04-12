.global campesino_ruso

campesino_ruso:
    @ i -> r0, j -> r1, res -> r2
    push {lr, r4}
    
    movw r2, #0

    b condicion

cuerpo:
    tst r1, #1
    addne r2, r2, r0
    subne r1, r1, #1

    lsl r0, r0, #1 
    moveq r1, r1, LSR #1

condicion:
    cmp r1, #1
    bhi cuerpo
    
    add r2, r2, r0
    mov r0, r2

    pop {lr, r4}
    bx lr
