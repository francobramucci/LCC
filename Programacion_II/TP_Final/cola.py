def validar_posicion(pos, tablero):


def solve(tablero):
    mov = [(1,0), (-1,0), (0,1), (0-1)]
    l = [pos]
    cont = 0
    matriz[pos[0]][pos[1]] = cont
    while l != []:
        cont += 1
        l = []
        for e in l:
            for m in mov:
                t = (e[0] + m[0], e[1] + m[1])
                if validar_posicion(t, matriz):
                    matriz[t[0]][t[1]] = cont
                if t == fin:
                    return
                l.append(t)

