# El tablero será una tupla. El primer elemento será un diccionario donde las llaves serán tuplas representando 
# la coordenada de cada barco y el valor será una tupla con un número del 1 a n, siendo n la cantidad de barcos,
# que representa a qué barco pertenece dicha celda y un bool que indica si se ha disparado a dicha celda. El 
# segundo elemento será una lista de n elementos, donde la enésima posicición será la cantidad de vidas del barco n.
#
# Un barco será una lista de tuplas donde cada elemento es una celda del barco.

def chequear_bordes(x: int, y: int, n: int):
    return not (x < 0 or x > n - 1 or y < 0 or y > n -1)

def chequear_adyacencia(x: int, y: int, tablero: tuple[dict[tuple[int, int], tuple[int, bool]], list[int]]):
    return not ((x,y) in tablero[0] or (x+1,y) in tablero[0] or (x,y+1) in tablero[0] or (x-1, y) in tablero[0] or (x,y-1) in tablero[0])

def agregaBarco(tablero: tuple[dict[tuple[int, int], tuple[int, bool]], list[int]], barco: list[tuple[int, int]]):
    valido = True
    i = 0
    while(valido == True):
        (x,y) = barco[i]
        if not chequear_bordes(x, y, 10) or not chequear_adyacencia(x, y, tablero):
            valido = False
        i += 1
    if i == len(barco):
        for coordenada in barco:
            num_barco = len(tablero[1])
            tablero[0][coordenada] = (num_barco, False)
            tablero[1].append(len(barco))


            


