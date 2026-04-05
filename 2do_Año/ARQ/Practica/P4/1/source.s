.data
array: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

.text
.global main
main:
    ldr r2, =array
    ldr r1, [r2]

    @-Primer linea--@
    ldr r0, [r2, #24]
    add r0, r1
    @---------------@

    @-Segunda linea-@
    ldr r3, [r2, #28]
    add r3, r1
    str r3, [r2, #36]
    @---------------@

    bx lr
