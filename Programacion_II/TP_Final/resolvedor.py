import subprocess

def generar_laberinto():
    resultado = subprocess.run(["./main", "EntradaLaberinto.txt"], capture_output=True)
    if resultado.returncode != 0:
        return False
    return True

def abrir_archivo(path:str, modo:str):
    archivo = open(path, modo) 
    return archivo

def inicializar_matriz(m, n, valor):
    matriz = []
    while(m):
        matriz.append([valor] * n)
        m -= 1
    return matriz

def inicializar_laberinto(dimension):
    tablero = inicializar_matriz(dimension, dimension, 0)
    visitados = inicializar_matriz(dimension, dimension, False)
    laberinto = dict()
    laberinto["dimension"] = dimension
    laberinto["tablero"] = tablero
    laberinto["visitados"] = visitados
    laberinto["inicio"] = (-1,-1)
    laberinto["objetivo"] = (-1,-1)

    return laberinto

def obtener_dimension(archivo):
    linea = archivo.readline()
    archivo.seek(0,0)
    return len(linea) - 1

def obtener_laberinto(archivo, laberinto):
    dimension = laberinto["dimension"]
    INF = dimension * dimension
    i = 0
    j = 0
    for l in archivo:
        for c in l[:-1]:
            if c == 'I':
                laberinto["inicio"] = (i,j)
            if c == 'X':
                laberinto["objetivo"] = (i,j)
            if c == '1':
                laberinto["tablero"][i][j] = INF
                laberinto["visitados"][i][j] = True
            else:
                laberinto["tablero"][i][j] = 0
            j += 1
        j = 0
        i += 1

def dentro_matriz(pos, m, n):
    x = pos[0]
    y = pos[1]
    return x >= 0 and x < n and y >= 0 and y < m

def validar_posicion(pos, laberinto, estado):
    dimension = laberinto["dimension"]
    return dentro_matriz(pos, dimension, dimension) and laberinto["visitados"][pos[0]][pos[1]] == estado

def resolver(laberinto):
    ini = laberinto["inicio"]
    fin = laberinto["objetivo"]
    matriz = laberinto["tablero"]
    visitados = laberinto["visitados"]

    movimientos = [(1,0), (-1,0), (0,1), (0,-1)]
    nivel = set()
    nivel.add(ini)
    visitados[ini[0]][ini[1]] = True
    distInicio = 0

    while nivel:
        distInicio += 1
        siguienteNivel = set()
        for celda in nivel:
            for m in movimientos:
                nuevaCelda = (celda[0] + m[0], celda[1] + m[1])
                if validar_posicion(nuevaCelda, laberinto, False):
                    x = nuevaCelda[0]
                    y = nuevaCelda[1]
                    matriz[x][y] = distInicio
                    visitados[x][y] = True
                    siguienteNivel.add(nuevaCelda)
                if nuevaCelda == fin:
                    return True
        nivel = siguienteNivel
    return False

def encontrar_camino(laberinto):
    matriz = laberinto["tablero"]
    fin = laberinto["objetivo"]
    ini = laberinto["inicio"]
    movimientos = [(1,0), (-1,0), (0,1), (0,-1)]
    celda = fin
    minimo = matriz[celda[0]][celda[1]]
    camino = [fin]
    while(celda != ini):
        i = 0
        nuevoCosto = minimo
        nuevaCelda = None
        while(nuevoCosto >= minimo):
            m = movimientos[i]
            nuevaCelda = (celda[0] + m[0], celda[1] + m[1])
            if(validar_posicion(nuevaCelda, laberinto, True)):
                nuevoCosto = matriz[nuevaCelda[0]][nuevaCelda[1]]
            i += 1
        celda = nuevaCelda
        minimo = nuevoCosto
        camino.append(celda)

    camino.reverse()
    return camino

def imprimir_matriz(matriz):
    for l in matriz:
        for c in l:
            print(c, end = '  ')
        print('\n')

def imprimir_lista(l):
    for e in l:
        print(e, end = ' ')
    print('\n')

def main():
    solucion = False
    salidaC = generar_laberinto()
    error = True
    if not salidaC:
        print("Error con el archivo de entrada. Se debe respetar el formato y las condiciones necesarias.")
        error = False
        return
    while(not solucion):
        if not error:
            generar_laberinto()
        archivoLaberinto = abrir_archivo("SalidaLaberinto.txt", "r")
        dimension = obtener_dimension(archivoLaberinto)
        laberinto = inicializar_laberinto(dimension)
        obtener_laberinto(archivoLaberinto, laberinto)
        imprimir_matriz(laberinto["tablero"])
        print()
        solucion = resolver(laberinto)
        if(solucion):
            camino = encontrar_camino(laberinto)
            imprimir_lista(camino)
        archivoLaberinto.close()

if __name__ == "__main__":
    main()


