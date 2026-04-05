.global main

main:
    @ add r3, r7, #1023

    movw r3, #1023
    add r3, r7

    @ sub r11, r12, r3, LSL #32
    
    mov r12, r11
