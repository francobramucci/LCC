# Ejercicio 1.
# Dada una lista de números se devuelve el mayor.
# mayor_while :: [Int] -> Int
# Entrada: [1,49,8]. Salida: 49
# Entrada: []. Salida: None. Se muestra por pantalla que la lista no posee elementos. 
def mayor_while(l):
    if len(l) == 0:
        print("La lista no posee elementos.")
        return
    i = 1 
    maxi = l[0]

    while i < len(l):
        if l[i] > maxi:
            maxi = l[i]
        i += 1

    return maxi

def test_mayor_while():
    assert mayor_while([1]) == 1
    assert mayor_while([1,4,19]) == 19

#------------------------------------------------------------------------------------#

# Dada una lista de números se devuelve el mayor.
# mayor_while :: [Int] -> Int
# Entrada: [1,49,8]. Salida: 49
# Entrada: []. Salida: Se muestra por pantalla que la lista no posee elementos. 
def mayor_for(l):
    if len(l) == 0:
        print("La lista no posee elementos.")
        return

    maxi = l[0]
    for e in l:
        if e > maxi:
            maxi = e

    return maxi

def test_mayor_for():
    assert mayor_for([1]) == 1
    assert mayor_for([1,4,19]) == 19

# Ejercicio 2
def segundo_mayor(l):
    if len(l) < 2:
        print("No hay suficientes elementos en la lista.")
        return
    maxi = l[0]
    smaxi = l[0]

    for e in l:
        if e > maxi:
            smaxi = maxi
            maxi = e

    return smaxi

