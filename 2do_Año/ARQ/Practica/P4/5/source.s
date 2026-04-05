.global main

main:
    @ 0xa400
    mov r2, #0xa4, 24

    @ 0x3d8
    mov r2, #0xf6, 30

    @ 0x17400
    mov r2, #0x5d, 22

    @ 0x1980
    mov r2, #0x66, 26

    @ 0xffffff00
    mvn r2, #0xff

    @ -1 = 0xffffffff
    mvn r2, #0x00

    bx lr
