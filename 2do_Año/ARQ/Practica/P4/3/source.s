.global main

main:
    ldr r6, =0xBEEFFACE
    movw r3, #0x8000
    str r6, [r3]

    bx lr
