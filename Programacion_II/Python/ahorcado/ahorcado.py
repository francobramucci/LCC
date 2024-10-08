import sys
from random import * 

def menu() -> int:
    op = 0
    while op != 1 and op != 2 and op != 3:
        clear()
        if op != 0: print("Ingrese una opción correcta")
        print("Bienvenido al ahorcado")
        op = int(input("1. Jugar contra la máquina\n2. Jugar contra otro jugador\n3. Salir\nIngrese una opción: "))
    return op

def clear():
    print("\n"*90)

def lineas_archivo(s):
    f = open(s, "r")
    i = 0
    for l in f:
        i += 1
    f.close()
    return i

def elegir_palabra(lemario):
    f = open(lemario, "r")
    j = 1

    cant_lineas = lineas_archivo(lemario)
    num_pal = randint(1, cant_lineas)
    
    while j != num_pal:
        f.readline()
        j += 1

    palabra_elegida = f.readline()
    palabra_elegida = palabra_elegida[:len(palabra_elegida) - 1]
    f.close()

    return palabra_elegida

def entrada(elegidas):
    letra = '1'
    while not letra.isalpha():
        letra = input("Ingrese una letra: ")
        if letra in elegidas:
            letra = '1'
    return letra

def vs_maquina():
    palabra_secreta = elegir_palabra()
    letras_correctas = set(palabra_secreta)
    vidas = 6
    adivinanza = ["_"] * len(palabra_secreta)
    letras_elegidas = {}

    while vidas > 0 and adivinanza != palabra_secreta:
        print(adivinanza)
        letra = entrada(letras_elegidas)
        if letra in letras_correctas():
            actualizar_tablero()
        else:
            vida -= 1





def main(lemario):
    modo = menu()
    if modo == 1:
        print("La palabra elegida es:", elegir_palabra(lemario))


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Ingresar el archivo lemario.")
        exit()
    main(sys.argv[1]) 
