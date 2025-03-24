import sys
import copy
from random import *
# Tomar un lemario y filtrar las palabras de longitud 5
# Tomar una palabra random y colocarla en una matriz de 5x5
# En base a dicha palabra colocar letras que formen palabras pertenecientes al lemario.

def makeTrie():
    return {}

def searchWordInTrie(root, pal):
    largo = len(pal)
    i = 0
    nodo = root
    while i < largo and pal[i] in nodo:
        nodo = nodo[pal[i]]
        i += 1
    return i == largo and "_fin_" in nodo

def searchPrefixInTrie(root, pref):
    i = 0
    nodo = root
    largo = len(pref)
    while i < largo-1 and pref[i] in nodo:
        nodo = nodo[pref[i]]
        i += 1
    return pref[i] in nodo

def insertTrie(root, pal:str):
    nodo = root 
    largo = len(pal)
    i = 0
    while i < largo:
        letra = pal[i]

        if i == largo-1:
            letra_siguiente = "_fin_"
        else:
            letra_siguiente = pal[i+1]

        if letra not in nodo:
            nodo[letra] = {letra_siguiente: {}}
        else:
            if letra_siguiente not in nodo[letra]:
                nodo[letra][letra_siguiente] = {}
        nodo = nodo[letra]
        i += 1

def palabrasFiltradasATrie(archivo, cond):
    trie = makeTrie()
    archivo.seek(0)
    for linea in archivo:
        linea = linea[:len(linea)-1]
        if cond(linea):
            insertTrie(trie, linea.lower())
    return trie


def palabraRandomLargoN(nodo, n):
    if n == 0:
        return '' if '_fin_' in nodo else -1
    if len(nodo) == 1 and '_fin_' in nodo:
        return -1

    hijos = trieNodeToSet(nodo)
    hijos = set(nodo.keys())
    hijos.discard('_fin_')

    letra = hijos.pop()
    pal = palabraRandomLargoN(nodo[letra], n-1)
    #print(pal) if pal != -1 else print()
    while len(hijos) > 0 and pal == -1:
        letra = hijos.pop()
        pal = palabraRandomLargoN(nodo[letra], n-1)
    if len(hijos) == 0 and pal == -1:
        return -1
    else:
        return ''.join([letra, pal])

def inicializarTablero(m, n):
    tab = {"filas":[[] for _ in range(m)], "columnas": [[] for _ in range(n)]}
    return tab

# tab almacenará una lista con todas las filas y una lista
# con todas las columnas

def trieNodeToSet(nodo):
    conjunto = set(nodo.keys())
    conjunto.discard('_fin_')
    return conjunto

def numeroFilas(tab):
    return len(tab["filas"])

def numeroColumnas(tab):
    return len(tab["columnas"])

def verificarEnFilaColumna(root, tab, fila, col):
    m = numeroFilas(tab)
    n = numeroColumnas(tab)

    largo_fila = len(tab["filas"][fila])
    largo_col = len(tab["columnas"][col])
    str_fila = ''.join(tab["filas"][fila])
    str_col = ''.join(tab["columnas"][col])
    #print("N° filas:", m, "N° columnas:", n, "largo_fila:", largo_fila, "largo_columna:", largo_col, "str_fila:", str_fila, "str_col:", str_col)

    if largo_fila == n:
        if largo_col == m:
            return searchWordInTrie(root, str_fila) and searchWordInTrie(root, str_col)
        if largo_col < m:
            return searchWordInTrie(root, str_fila) and searchPrefixInTrie(root, str_col)
    if largo_col == m:
        return searchPrefixInTrie(root, str_fila) and searchWordInTrie(root, str_col)
    return searchPrefixInTrie(root, str_fila) and searchPrefixInTrie(root, str_col)

def emptySet(set):
    return len(set) == 0


def agregarLetraTablero(letra, tab, fila, col):
    tab["filas"][fila][col] = letra
    tab["columnas"][col][fila] = letra


def crearCrucigrama(root, nodo, tab, fila):
    m = numeroFilas(tab)
    n = numeroColumnas(tab)
    col = len(tab["filas"][fila])
    incremento = 0

    if fila == m-1 and col == n:
        # El tablero está completo
        return tab

    if col == n-1:
        #La fila está llena, paso a la siguiente
        incremento = 1

    letras = trieNodeToSet(nodo)
    if emptySet(letras):
        return -1

    condicion = False
    set_vacio = False
    tab["filas"][fila].append('')
    tab["columnas"][col].append('')
    aux = -1

    while not set_vacio and (aux == -1 or not condicion):
        letra = letras.pop()
        agregarLetraTablero(letra, tab, fila, col)
        condicion = verificarEnFilaColumna(root, tab, fila, col)
        #print(tab, condicion)
        set_vacio = emptySet(letras)
        if condicion:
            aux = copy.deepcopy(tab)
            aux = crearCrucigrama(root, nodo[letra] if incremento != 1 else root, aux, min(fila + incremento, m-1))
    if set_vacio and (aux == -1 or not condicion):
        # No tengo mas letras que probar y no es valido
        return -1
    else:
        return aux


def main(path):
    tab = inicializarTablero(5,3)
    print(tab)
    archivo = open(path, "r")
    trie = palabrasFiltradasATrie(archivo, lambda linea: len(linea) == 4)
    trie2 = palabrasFiltradasATrie(archivo, lambda linea: len(linea) <= 10)
    archivo.close()

    print(crearCrucigrama(trie2, trie2, tab, 0))
#    trie3 = {}
#    for pal in ["pana", "aros", "sera", "olas", "paso", "arel", "nora", "esas"]:
#        insertTrie(trie3, pal)
#    print(crearCrucigrama(trie3, trie3, tab, 0))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Ingresar el archivo lemario.")
        exit()
    main(sys.argv[1])
