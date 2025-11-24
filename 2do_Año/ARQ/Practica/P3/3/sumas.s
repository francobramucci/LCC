.data
n1: .byte 100
n2: .byte 120
n3: .byte -63
n4: .byte -56
n5: .byte -91

.text
.global main

main:
    # S1: CF = 0, OF = 1
    movb n2, %al
    addb n1, %al


    # S2: CF = 1, OF = 0
    movb n4, %bl
    addb n3, %bl

    # S3: CF = 1, OF = 1
    movb n5, %cl
    addb n3, %cl

    # S4: CF = 1, OF = 1. Notar que CF se activa ya que se realiza la resta
    # sin signo 120 - 200 para la que necesita hacer un borrow.
    movb n2, %dl
    subb n4, %dl
    
    # S5: CF = 0, OF = 1
    movb n5, %r8b
    subb n2, %r8b

    ret
