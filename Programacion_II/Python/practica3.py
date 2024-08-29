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
