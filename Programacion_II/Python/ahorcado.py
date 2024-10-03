import sys
from random import * 

def menu() -> int:
    op = 0
    while op != 1 and op != 2 and op != 3:
        clear()
        print("Bienvenido al ahorcado")
        op = int(input("1. Jugar contra la máquina\n2. Jugar contra otro jugador\n3. Salir\nIngrese una opción: "))
    return op

def clear():
    print("\n"*90)

def elegir(lemario):
    f = open(lemario, "r")
    i = 0
    for l in f: i += 1
    cant_lineas = i
    randint(1, cant_lineas)

def main(lemario):
    modo = menu()
    if modo == 1:
        vs_maquina(lemario)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Ingresar el archivo lemario.")
        exit()
    main(sys.argv[1]) 
