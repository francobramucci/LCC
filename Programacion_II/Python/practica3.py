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
        if l[0] <= l[1]:
            return ordenada(l[1:])
        else: 
            return False

#Lucas, dado dos número iniciales y un índice, devolver el valor de la secuencia en dicho índice 

def lucas(a, b, n):
    if n==0:
        return a
    return lucas(b, a+b, n-1)


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
    ini = 0
    end = length(l)-1
    mid = (ini+end) // 2
