import sys
from random import * 

def menu() -> int:
    op = 0
    while op != 1 and op != 2 and op != 3:
        clear()
        if op != 0: print("Ingrese una opción correcta")
        print("Bienvenido al ahorcado")
        op = input("1. Jugar contra la máquina\n2. Jugar contra otro jugador\n3. Salir\nIngrese una opción: ")
        if op.isdigit():
            op = int(op)
        else:
            op = -1
    return op

def clear():
    print("\n"*90)

def lineas_archivo(s:str) -> int:
    f = open(s, "r")
    i = 0
    for l in f:
        i += 1
    f.close()
    return i

def elegir_palabra(lemario:str) -> str:
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

def entrada(elegidas:set) -> str:
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


def letras_correctas(palabra:str) -> dict[str, list[int]]:
    dic = {}
    i = 0
    for l in palabra:
        if l not in dic.keys():
            dic[l] = [i]
        else:
            dic[l].append(i)
        i += 1
    return dic


def actualizar_tablero(l:str, letras:dict, adivinanza) -> list[str]:
    for i in letras[l]:
        adivinanza[i] = l
    return adivinanza


def mostrar_tablero(adivinanza:list[str], vidas:int, elegidas:set):
    for e in adivinanza:
        print(e, end = ' ')
    print("Vidas:", vidas)
    print("Letras elegidas:", end = ' ')
    for e in elegidas:
        print(e, end = ' ')
    print()

    
def vs_maquina(lemario: str) -> tuple[bool,str]:
    palabra_secreta = elegir_palabra(lemario)
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
        clear();

    if vidas > 0:
        return (True, palabra_secreta)
    return (False, palabra_secreta)

#def vs_jugador():
    


def main(lemario):
    modo = menu()
    while modo != 3:
        if modo == 1:
            clear()
            resultado = vs_maquina(lemario)
            print("Ganaste, la palabra era" if resultado[0] else "Perdiste, la palabra era", f'"{resultado[1]}"')
            input("Presione enter para continuar:")
        modo = menu()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Ingresar el archivo lemario.")
        exit()
    main(sys.argv[1]) 
