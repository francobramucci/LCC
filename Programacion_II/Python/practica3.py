#1
def posicionesMultiplo(l,n):
    if n >= len(l):
        return [l[0]]
    else:
        res = posicionesMultiplo(l[n:], n)
        res.append(l[0])
        return res
print(posicionesMultiplo([1,2,3,4,5,6,7],2))

#2
def sumaad(l):
    def aux(l,r = [l[0]]):
        if l[1:] == []:
            return r
        else:
            r.append(l[1]+r[len(r)-1])
            return aux(l[1:], r)
    return aux(l)

def sumaad1(l):
    def aux(l,r):
        if l == []:
            return r
        else:
            r.append(l[0]+r[len(r)-1])
            return aux(l[1:], r)
    return aux(l, [0])[1:]

#3
def elimina(l):
    return l[1:len(l)-1]

#4
def ordenada(l):
    if l[1:] == []:
        return True
    else:
        if l[0] < l[1]:
            return ordenada(l[1:])
        else: 
            return False

#Lucas, dado dos número iniciales y un índice, devolver el valor de la secuencia en dicho índice 

# Toma 3 numeros y hace una sucesion de fibonacci iniciando con los primeros 2 numeros
#y retorna el numero n del la sucesion

def lucasFL(f1 , f2 , n):
    l = [f1,f2]
    for i in range(n):
        l.append(l[-2] + l[-1])
    return l

print(lucasFL(2,1,9))

# Falta hacer lucasF que retorna el valor en n y no la lista completa

def lucasR(f1 , f2 , n):
    if n > 0:
        return lucasR(f2 , f1+f2 , n-1)
    else:
        return f2

print(lucasR(2,1,9))

#5
def duplicado(l):
    aux = sorted(l)
    for i in range(len(aux)-2):
        if aux[i] == aux[i+1]:
            return True
    return False

#6
def eliminaDuplicados(l):
    l.sort()
    temp = l[0]
    res = []
    for i in range(len(l)):
        if temp != l[i]:
            res.append(temp)
            temp = l[i]
    res.append(temp)
    return res

#7
def contdist(l):
    return len(eliminaDuplicados(l))

#8
def BusquedaDicotomica(l,s):
    l.sort()
    ini = 0
    end = len(l)-1
    mid = (end+ini)//2
    while ini != end:
        if s == l[mid]:
            return True
        if s > l[mid]:
            ini = mid
            mid = (end+ini)//2
        if s < l[mid]:
            end = mid
            mid = (end+ini)//2
            

            
def diablo(l):
    for i in range(-1,-len(l)-1,-1):
        print(l[i])
         



        
    





