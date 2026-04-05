.global main

main:
    @ a) 0xc0000034
    mov r2, #0xd3, 2
    
    @ b) 0x12340000. No es posible

    @ c) 0x77777777. No es posible

    @ d) 0xffffffff
    mvn r2, #0x00 

    @ e) 0xfffffffe
    mvn r2, #0x01
    
    bx lr
