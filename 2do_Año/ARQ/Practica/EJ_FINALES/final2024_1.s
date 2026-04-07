.data
str: .asciz "El resultado de la suma es: %d\n"
str1: .asciz "Todos los argumentos deben ser positivos\n"

.text
.global calculo

calculo:
    push {r4, lr}
    @ r0 -> a, r1 -> b, r2 -> c, r3 -> d.
    ldr r4, [sp, #8]

    cmp r0, #0
    bmi negativo

    cmp r1, #0
    bmi negativo

    cmp r2, #0
    bmi negativo

    cmp r3, #0
    bmi negativo

    cmp r4, #0
    bmi negativo

    add r1, r1, r0
    add r1, r1, r2
    add r1, r1, r3
    add r1, r1, r4
    
    mov r4, r1

    ldr r0, =str
    bl printf
    
    mov r0, r4
    pop {r4, lr}
    bx lr

negativo:
    bl foo
    pop {r4, lr}
    bx lr

foo:
    ldr r0, =str1
    bl printf
    mov r0, #-1
    bx lr
    





