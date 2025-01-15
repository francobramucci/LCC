import subprocess

def generar_laberinto():
    subprocess.run(["./main", "EntradaLaberinto.txt"])

def abrir_archivo(path:str, modo:str):
    archivo = open(path, modo) 
    return archivo

def inicializar_matriz(m, n):
    matriz = [[]] * m
    while(m > 0):
        m -= 1
        matriz[m] = [0] * n
    return matriz

def inicializar_laberinto(dimension):
    matriz = inicializar_matriz(dimension, dimension)
    laberinto = dict()
    laberinto["tablero"] = matriz
    laberinto["inicio"] = (-1,-1)
    laberinto["objetivo"] = (-1,-1)

    return laberinto

def obtener_dimension(archivo):
    linea = archivo.readline()
    archivo.seek(0,0)
    return len(linea)

def obtener_laberinto(archivo, laberinto):
    i = 0
    j = 0

    for l in archivo:
        for c in l:
            if c == 'I':
                laberinto["inicio"] = (i,j)
            if c == 'X':
                laberinto["objetivo"] = (i,j)
            if c == '1':
                print("hola")
                laberinto["tablero"][i][j] = 1
            print(i,j)
            laberinto["tablero"][i][j] = 0
            j += 1
        j = 0
        i += 1

if __name__ == "__main__":
    generar_laberinto()
    archivo_laberinto = abrir_archivo("SalidaLaberinto.txt", "r")
    dimension = obtener_dimension(archivo_laberinto)
    laberinto = inicializar_laberinto(dimension)
    obtener_laberinto(archivo_laberinto, laberinto)
    print(laberinto)

