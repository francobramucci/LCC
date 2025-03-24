from io import StringIO
from resolvedor import *

def test_inicializar_matriz():
    resultado = inicializar_matriz(2, 2, 0)
    esperado = [[0, 0], [0, 0]]
    assert resultado == esperado

    assert inicializar_matriz(0, 5, False) == []
    assert inicializar_matriz(5, 0, 'c') == []

    matriz_grande = inicializar_matriz(1000, 1000, 0)
    assert len(matriz_grande) == 1000
    assert len(matriz_grande[0]) == 1000
    assert matriz_grande[0][0] == 0

def test_inicializar_laberinto():
    dimension = 5
    laberinto = inicializar_laberinto(dimension)

    assert isinstance(laberinto, dict), "El laberinto deberia ser un diccionario."
    assert laberinto["dimension"] == dimension, "La dimensión no coincide."
    assert laberinto["inicio"] == (-1, -1), "El inicio debería estar sin definir (-1, -1)."
    assert laberinto["objetivo"] == (-1, -1), "El objetivo deberia estar sin definir (-1, -1)."


    assert all(celda == 0 for fila in laberinto["tablero"] for celda in fila), "Todas las celdas del tablero deberian estar en 0."
    assert all(celda is False for fila in laberinto["visitados"] for celda in fila), "Todas las celdas de visitados deberian estar en False."

def test_obtener_laberinto():
    laberinto = {
        "dimension": 4,
        "tablero": [[0]*4 for _ in range(4)],
        "visitados": [[False]*4 for _ in range(4)],
        "inicio": (-1, -1),
        "objetivo": (-1, -1)
    }

    archivo = StringIO("I001\n1110\n0X00\n0000\n")

    obtener_laberinto(archivo, laberinto)

    assert laberinto["tablero"][1][0] == laberinto["tablero"][1][1] == 16
    assert laberinto["visitados"][1][0] is True
    assert laberinto["visitados"][1][1] is True
    assert laberinto["tablero"][0][0] == 0
    assert laberinto["tablero"][2][1] == 0
    assert laberinto["inicio"] == (0, 0)
    assert laberinto["objetivo"] == (2, 1)

def test_dentro_matriz():
    assert dentro_matriz((1, 1), 3, 3) == True
    assert dentro_matriz((0, 0), 3, 3) == True
    assert dentro_matriz((2, 2), 4, 4) == True
    assert dentro_matriz((-1, 1), 3, 3) == False
    assert dentro_matriz((0, -1), 3, 3) == False
    assert dentro_matriz((4, 0), 4, 4) == False
    assert dentro_matriz((0, 5), 5, 5) == False

def test_validar_posicion():
    laberinto = {
        "dimension": 4,
        "tablero": [[0]*4 for _ in range(4)],
        "visitados": [[False]*4 for _ in range(4)],
        "inicio": (-1, -1),
        "objetivo": (-1, -1)
    }

    laberinto["tablero"][0][0] = 0
    laberinto["visitados"][0][0] = True

    assert validar_posicion((1,0), laberinto, False) == True
    assert validar_posicion((0,0), laberinto, True) == True

def test_resolver():
    laberinto = {
        "dimension": 5,
        "tablero": [[0]*5 for _ in range(5)],
        "visitados": [[False]*5 for _ in range(5)],
        "inicio": (0, 0),
        "objetivo": (4, 4)
    }

    assert resolver(laberinto) == True

    laberinto["tablero"] = [
        [0, 1, 0, 0, 0],
        [0, 1, 0, 1, 0],
        [0, 1, 0, 1, 0],
        [0, 1, 0, 1, 0],
        [0, 0, 0, 1, 0]
    ]
    laberinto["visitados"] = [[False]*5 for _ in range(5)]

    assert resolver(laberinto) == True

def test_encontrar_camino():
    laberinto = {
        "dimension": 5,
        "tablero": [[0]*5 for _ in range(5)],
        "visitados": [[False]*5 for _ in range(5)],
        "inicio": (0, 0),
        "objetivo": (4, 4)
    }

    laberinto["tablero"] = [
        [0, 25, 10, 12, 13],
        [1, 25, 9, 25, 14],
        [2, 25, 8, 25, 15],
        [3, 25, 7, 25, 16],
        [4, 5, 6, 25, 17]
    ]
    laberinto["visitados"] = [
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1]
    ]

    assert encontrar_camino(laberinto) == [(1,1), (2,1), (3,1), (4,1), (5,1), (5,2), (5,3), (4,3), (3,3), (2,3), (1,3), (1,4), (1,5), (2,5), (3,5), (4,5), (5,5)]

