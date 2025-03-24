import subprocess

def generar_laberinto(comandoYArgs:list[str]) -> bool:
    """
    Ejecuta un programa en C para obtener un archivo con un laberinto.

    :param comandoYArgs: lista con el comando como primer elemento y argumentos
    en los siguientes.

    :returns: si se pudo generar el laberinto correctamente.
    """
    resultado = subprocess.run(comandoYArgs, stderr=subprocess.PIPE, text=True)
    if resultado.returncode != 0:
        print(resultado.stderr)
        return False
    return True

def abrir_archivo(path:str, modo:str):
    """
    Recibe la ruta de un archivo y el modo de apertura y abre dicho archivo.

    :param path: ruta del archivo.
    :param: modo de apertura del archivo.

    :returns: el objeto archivo.
    """
    archivo = open(path, modo)
    return archivo

def inicializar_matriz(m:int, n:int, valor) -> list:
    """
    Inicializa una matriz de m*n con un valor.

    :param m: cantidad de filas de la matriz.
    :param n: cantidad de columnas de la matriz.
    :param valor: valor de relleno de la matriz.

    :returns: la matriz inicializada.
    """
    if m == 0 or n == 0:
        return []
    matriz = []
    while(m):
        matriz.append([valor] * n)
        m -= 1
    return matriz

def inicializar_laberinto(dimension:int) -> dict:
    """
    Inicializa un laberinto en forma de diccionario.

    :param dimension: el tamaño del laberinto.

    :returns: diccionario que almacena informacion sobre el laberinto.
    """
    tablero = inicializar_matriz(dimension, dimension, 0)
    visitados = inicializar_matriz(dimension, dimension, False)
    laberinto = dict()
    laberinto["dimension"] = dimension
    laberinto["tablero"] = tablero
    laberinto["visitados"] = visitados
    laberinto["inicio"] = (-1,-1)
    laberinto["objetivo"] = (-1,-1)

    return laberinto

def obtener_dimension(archivo) -> int:
    """
    Recibe un archivo con una matriz y devuelve el ancho(alto) de la misma.

    :param archivo: archivo con la matriz que representa el laberinto.

    :returns: dimension del laberinto.
    """
    linea = archivo.readline()
    archivo.seek(0,0)
    return len(linea) - 1

def obtener_laberinto(archivo, laberinto:dict):
    """
    Recibe un archivo con una matriz y un diccionario con informacion del
    laberinto y guarda informacion en dicho diccionario. En las posiciones
    donde hay obstaculos se almacena el valor dimension*dimension ya que es
    imposible tener dicha distancia entre dos casillas en el laberinto.

    :param archivo: archivo con la matriz del laberinto.
    :param laberinto: diccionario con informacion del laberinto.

    :returns: laberinto.
    """
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

def dentro_matriz(pos:tuple[int, int], m:int, n:int) -> bool:
    """
    Verifica que un punto esta dentro de una matriz de m*n.

    :param pos: una tupla que representa un punto.
    :param m: cantidad de filas de la matriz.
    :param n: cantidad de columnas de la matriz.

    :returns: si el punto esta dentro de la matriz.
    """
    x = pos[0]
    y = pos[1]
    return x >= 0 and x < n and y >= 0 and y < m

def validar_posicion(pos:tuple[int, int], laberinto:dict, estado:bool) -> bool:
    """
    Valida si un punto pertenece al laberinto y si el mismo esta visitado o no.

    :param estado: valor para verificar si el punto ya ha sido visitado o no.

    :returns: validez del punto.
    """
    dimension = laberinto["dimension"]
    return dentro_matriz(pos, dimension, dimension) and laberinto["visitados"][pos[0]][pos[1]] == estado

def resolver(laberinto:dict) -> bool:
    """
    Parte del punto de inicio y recorre por niveles (donde cada nivel es un
    conjunto de puntos que estan a una misma distancia del inicio) hasta
    encontrar el objetivo o quedarse sin celdas por recorrer.

    :returns: si hay un camino desde el inicio hasta el objetivo.
    """
    ini = laberinto["inicio"]
    fin = laberinto["objetivo"]
    matriz = laberinto["tablero"]
    visitados = laberinto["visitados"]

    movimientos = [(1,0), (-1,0), (0,1), (0,-1)]
    nivel = set()
    nivel.add(ini)
    visitados[ini[0]][ini[1]] = True
    distInicio = 0
    haySolucion = False

    while nivel and not haySolucion:
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
                    haySolucion = True
        nivel = siguienteNivel
    if haySolucion:
        return True
    return False

def encontrar_camino(laberinto:dict) -> bool:
    """
    Parte desde el final y avanza hasta llegar al inicio eligiendo el camino
    mas corto posible. Esta funcion se ejecuta si existe una solucion al
    laberinto.

    :returns: celdas del camino desde el inicio hasta el objetivo.
    """
    matriz = laberinto["tablero"]
    fin = laberinto["objetivo"]
    ini = laberinto["inicio"]
    movimientos = [(1,0), (-1,0), (0,1), (0,-1)]
    celda = fin
    minimo = matriz[celda[0]][celda[1]]
    camino = [(fin[0]+1, fin[1]+1)]
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
        camino.append((celda[0]+1, celda[1]+1))

    camino.reverse()
    return camino

def imprimir_lista(l:list):
    """
    Recibe una lista e imprime sus elementos separados por espacios.

    :param l: lista a imprimir.
    """
    for e in l:
        print(e, end = ' ')

