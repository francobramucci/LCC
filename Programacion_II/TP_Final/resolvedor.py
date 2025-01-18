import subprocess

def generar_laberinto():
    subprocess.run(["./main", "EntradaLaberinto.txt"])

def abrir_archivo(path:str, modo:str):
    archivo = open(path, modo) 
    return archivo

def inicializar_matriz(m, n):
    matriz = []
    while(m):
        matriz.append([0] * n)
        m -= 1
    return matriz

def inicializar_laberinto(dimension):
    matriz = inicializar_matriz(dimension, dimension)
    laberinto = dict()
    laberinto["dimension"] = dimension
    laberinto["tablero"] = matriz
    laberinto["inicio"] = (-1,-1)
    laberinto["objetivo"] = (-1,-1)

    return laberinto

def obtener_dimension(archivo):
    linea = archivo.readline()
    archivo.seek(0,0)
    return len(linea) - 1

def obtener_laberinto(archivo, laberinto):
    i = 0
    j = 0
    for l in archivo:
        for c in l[:-1]:
            if c == 'I':
                laberinto["inicio"] = (i,j)
            if c == 'X':
                laberinto["objetivo"] = (i,j)
            if c == '1':
                laberinto["tablero"][i][j] = -1
            else:
                laberinto["tablero"][i][j] = -2
            j += 1
        j = 0
        i += 1

def dentro_matriz(pos, m, n):
    x = pos[0]
    y = pos[1]
    return x >= 0 and x < n and y >= 0 and y < m

def validar_posicion(pos, laberinto):
    dimension = laberinto["dimension"]
    x = pos[0]
    y = pos[1]
    return laberinto["tablero"][x][y] != -1 and laberinto["tablero"][x][y] == -2 and dentro_matriz(pos, dimension, dimension)

def resolver(laberinto):
    ini = laberinto["inicio"]
    fin = laberinto["objetivo"]
    matriz = laberinto["tablero"]
    dimension = laberinto["dimension"]

    mov = [(1,0), (-1,0), (0,1), (0,-1)]
    s = set()
    s.add(ini)
    cont = 0
    matriz[ini[0]][ini[1]] = cont
    while s:
        cont += 1
        aux = set()
        for e in s:
            for m in mov:
                t = (e[0] + m[0], e[1] + m[1])
                if validar_posicion(t, laberinto):
                    matriz[t[0]][t[1]] = cont
                    aux.add(t)
                if t == fin:
                    print(cont)
                    imprimir_matriz(matriz)
                    return
        s = aux
    imprimir_matriz(matriz)

def imprimir_matriz(matriz):
    for l in matriz:
        for c in l:
            print(c, end = '  ')
        print('\n')

if __name__ == "__main__":
    generar_laberinto()
    archivoLaberinto = abrir_archivo("SalidaLaberinto.txt", "r")
    dimension = obtener_dimension(archivoLaberinto)
    laberinto = inicializar_laberinto(dimension)
    obtener_laberinto(archivoLaberinto, laberinto)
    print(laberinto)
    resolver(laberinto)

