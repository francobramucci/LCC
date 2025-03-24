import sys
from random import *


def menu() -> int:
    op = 0
    while op != 1 and op != 2 and op != 3:
        clear()
        if op != 0:
            print("Ingrese una opción correcta")
        print("Bienvenido al ahorcado")
        op = input(
            "1. Jugar contra la máquina\n2. Jugar contra otro jugador\n3. Salir\nIngrese una opción: ")
        if op.isdigit():
            op = int(op)
        else:
            op = -1
    return op


def clear():
    print("\n"*90)


def lineas_archivo(archivo) -> int:
    i = 0
    for l in archivo:
        i += 1
    return i


def elegir_palabra(archivo, cant_lineas: int) -> str:
    archivo.seek(0)

    j = 1
    num_pal = randint(1, cant_lineas)

    while j != num_pal:
        archivo.readline()
        j += 1

    palabra_elegida = archivo.readline()
    palabra_elegida = palabra_elegida[:len(palabra_elegida) - 1]

    return palabra_elegida


def entrada(elegidas: set) -> str:
    letra = '1'
    while not letra.isalpha():
        letra = input("Ingrese una letra: ")
        if letra in elegidas:
            print("Letra ya elegida")
            letra = '1'
        if len(letra) > 1:
            print("Ingrese solo un caracter")
            letra = '1'
        else:
            print("Ingrese un caracter válido")
    return letra


def letras_correctas(palabra: str) -> dict[str, list[int]]:
    dic = {}
    i = 0
    for l in palabra:
        if l not in dic.keys():
            dic[l] = [i]
        else:
            dic[l].append(i)
        i += 1
    return dic


def actualizar_tablero(l: str, letras: dict, adivinanza) -> list[str]:
    for i in letras[l]:
        adivinanza[i] = l
    return adivinanza


def mostrar_tablero(adivinanza: list[str], vidas: int, elegidas: set):
    for e in adivinanza:
        print(e, end=' ')
    print("Vidas:", vidas)
    print("Letras elegidas:", end=' ')
    for e in elegidas:
        print(e, end=' ')
    print()


def jugar(palabra_secreta: str) -> tuple[bool, str]:
    correctas = letras_correctas(palabra_secreta)
    cant_diferentes = len(correctas.keys())
    vidas = 6
    adivinanza = ["_"] * len(palabra_secreta)
    letras_elegidas = set()

    while vidas > 0 and cant_diferentes != 0:
        mostrar_tablero(adivinanza, vidas, letras_elegidas)
        letra = entrada(letras_elegidas)
        letras_elegidas.add(letra)
        if letra in correctas.keys():
            adivinanza = actualizar_tablero(letra, correctas, adivinanza)
            cant_diferentes -= 1
        else:
            vidas -= 1
        clear()

    if vidas > 0:
        return (True, palabra_secreta)
    return (False, palabra_secreta)


def ingresar_palabra() -> str:
    incorrecto = 1
    palabra = ""
    while incorrecto:
        incorrecto = 0
        palabra = input("Ingrese la palabra secreta:")
        for letra in palabra:
            if not letra.isalpha():
                incorrecto = 1
    return palabra


def mensaje_resultado(resultado: tuple[bool, str]):
    print("Ganaste, la palabra era" if resultado[0] else "Perdiste, la palabra era", f'"{
          resultado[1]}"')
    input("Presione enter para continuar:")


def main(lemario):
    modo = menu()
    palabra_secreta = ''
    while modo != 3:
        if modo == 1:
            archivo = open(lemario, "r")
            largo = lineas_archivo(archivo)
            clear()
            palabra_secreta = elegir_palabra(archivo, largo)

        if modo == 2:
            palabra_secreta = ingresar_palabra()

        resultado = jugar(palabra_secreta)
        mensaje_resultado(resultado)
        modo = menu()


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Ingresar el archivo lemario.")
        exit()
    main(sys.argv[1])
