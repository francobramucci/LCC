.global main
main:
    movw r3, #0x8000        @ r3 = 0x8000

    str r6, [r3, #12]       @ r3 = 0x8000
    strb r7, [r3], #4       @ r3 = 0x8004
    ldrh r5, [r3], #8       @ r3 = 0x800c
    ldr r12, [r3, #12]!     @ r3 = 0x8018

    mov r0, r3

    bx lr

@ En realidad este codigo no puede ejecutarse ya que produce seg fault
@ debido a que se está escribiendo en una dirección de memoria indebida.
