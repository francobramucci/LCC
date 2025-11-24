.data
a: .long 1, 2, 3, 4
g: .quad 0x1122334455667788
msg: .asciz "Imprime %c\n"

.text
.global main
main:
    subq $8, %rsp               # rsp = 0x7fffffffebc0
    movq $g, %rax               # rax = 0x404038
    movl g+4, %eax              # rax = 0x11223344
    movq $3, %rbx               # rbx = 0x03
    movb a(, %rbx, 4), %al      # rax = 0x11223304
    leaq msg, %rdi              # rdi = 0x404040
    movb (%rdi, %rbx, 2), %sil  # sil = 0x65 ('e')
    xorl %eax, %eax             # rax = 0x0
    call printf                 # rax = 0xA
    addq $8, %rsp               # rsp = 0x7fffffffebc8
    ret

# Etiqueta          Dirección de memoria            Valor almacenado
# a                 0x404028                        1 
#                   0x404029                        0
#                   0x40402A                        0
#                   0x40402B                        0
#                   0x40402C                        2
#                   0x40402D                        0
#                   0x40402E                        0
#                   0x40402F                        0
#                   0x404030                        3
#                   0x404031                        0
#                   0x404032                        0
#                   0x404033                        0
#                   0x404034                        4
#                   0x404035                        0
#                   0x404036                        0
#                   0x404037                        0
# g                 0x404038                        0x88
#                   0x404039                        0x77
#                   0x40403A                        0x66
#                   0x40403B                        0x55
#                   0x40403C                        0x44
#                   0x40403D                        0x33
#                   0x40403E                        0x22
#                   0x40403F                        0x11
# msg               0x404040                        'I'
#                   0x404041                        'm'
#                   0x404042                        'p'
#                   0x404043                        'r'
#                   0x404044                        'i'
#                   0x404045                        'm'
#                   0x404046                        'e'
#                   0x404047                        ' '
#                   0x404048                        '%'
#                   0x404049                        'c'
#                   0x40404A                        '\n'
#                   0x40404B                        0x0
