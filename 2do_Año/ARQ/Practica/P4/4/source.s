.global main

main:
    mov r7, #0x8c, 4    @ Se realiza ROR con 4 bits, r7 = 0xc0000008
    mov r7, #0x42, 30   @ r7 = 0x108
    mvn r7, #2          @ Se mueve con not, r7 = not(#2) = 0xfffffffd
    mvn r7, #0x8c, 4    @ r7 = 0x3fffffff7

    bx lr
