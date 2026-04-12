.data
a: .long 1, 2, 3, 4
b: .long 2, 3, 4, 5
str: .asciz "La suma es: %d\n"

.text
.global main

main:
    push {r4, lr}
    
    ldr r0, =a
    ldr r1, =b
    mov r2, #4

    bl suma
    mov r1, r0
    ldr r0, =str
    bl printf
    
    movw r0, #0
    pop {r4, lr}
    bx lr

suma:
    @ r0 -> a, r1 -> b, r2 -> L, r3 -> result
    push {r4}
    sub sp, sp, #12     @ Reservo espacio para variables locales
    str r0, [sp, #8]     
    str r1, [sp, #4]
    str r2, [sp]
    
    movw r3, #0

    subS r2, r2, #1
    bmi fin

loop:
    ldr r4, [r0, r2, LSL #2]
    add r3, r3, r4
    ldr r4, [r1, r2, LSL #2]
    add r3, r3, r4
    subS r2, r2, #1
    bpl loop

fin:
    mov r0, r3
    add sp, sp, #12
    pop {r4}
    bx lr 
