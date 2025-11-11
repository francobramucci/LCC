.data
str: .asciz "El valor de salida del programa es: %d\n"

.text
.global main

main:
    # Resto del programa...
    movb $80, %al
    # Supongamos que hasta este punto %al se encuentra con el valor 80
    
    # Guardamos el valor para no perderlo cuando cambiemos %rax en la llamada
    # a printf
    movzbl %al, %ebx
    
    movq $str, %rdi
    movl %ebx, %esi
    movq $0, %rax
    call printf
    
    # Recuperamos el valor de %al
    movl %ebx, %eax

    ret
