.global main

main:
    movq $0x1122334455667788, %rax
    addq $0x1122334455667788, %rax
    ret


# source.s: Assembler messages:
# source.s:5: Error: operand type mismatch for `add'
# Esto ocurre ya que los valores inmediatos pueden tener un tamaño máximo de 32
# bits excepto en la función mov que pueden ser de 64 bits.

