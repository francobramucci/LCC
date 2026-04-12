.global main

main:
    movw r0, #3
    movw r1, #1
    mov r0, r1, lsl r0

    bx lr
