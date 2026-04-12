.data
a: .float 1.0, 2.0, 3.0, 4.0, 5.0
b: .float 2.0, 4.0, 6.0, 8.0, 10.0
str: .asciz "%f\n"
str1: .asciz "La suma de las componentes es: %f\n"

.bss
c: .skip 20

.text
.global main

main:
    push {r4, r5, r6, r7, r8, lr}
    @ r4 -> dir.a, r5 -> dir.b, r6 -> dir.c, r7 -> contador
    ldr r8, =str
    movw r7, #0
    ldr r4, =a
    ldr r5, =b
    ldr r6, =c
    vmov.f32 s2, r7 @

loop:
    vldr.f32 s0, [r4]
    vldr.f32 s1, [r5]
    vadd.f32 s0, s0, s1
    vstr.f32 s0, [r6]

    vadd.f32 s2, s2, s0

    vcvt.f64.f32 d0, s0 @
    
    mov r0, r8
    vmov r2, r3, d0
    bl printf

    add r4, r4, #4
    add r5, r5, #4
    add r6, r6, #4

    add r7, #1
    cmp r7, #5
    blt loop
    
    ldr r0, =str1
    vcvt.f64.f32 d0, s2
    vmov r2, r3, d0
    bl printf
    
    movw r0, #0
    pop {r4, r5, r6, r7, r8, lr}
    bx lr

    



    
    
    
    
