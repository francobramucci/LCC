#1
#a
def cantVecesWhile(l,e):
    i = 0
    cont = 0
    while i < len(l):
        if l[i] == e:
            cont += 1
        i += 1
    return cont

#b
def cantVecesFor(l,e):
    cont = 0
    for x in l:
        if x == e:
            cont += 1
    return cont

#c
def cantVecesRec(l,e):
    if l == []:
        return 0
    if l[0] == e:
        return 1 + cantVecesRec(l[1:], e)
    return cantVecesRec(l[1:], e)

#2
def elementosDistintos(l,e):
    res = []
    for x in l:
        if x != e and not x in res:
            res.append(x)
    return res

#3
def cantDistintos(l,e):
    if l == []:
        return 0
    if l[0] != e and cantVecesRec(l, l[0]) == 1:
        return 1 + cantDistintos(l[1:], e)
    return cantDistintos(l[1:], e)

#4
d
#4ef elementosDistintosCola(l,e,r=[]):
    if l == []:
        return r
    if l[0] != e and not l[0] in r:
        r.append(l[0])
    return elementosDistintosCola(l[1:], e, r)


def elementosDistintosRec(l,e):
    if l == []:
        return []
    if l[0] != e and cantVecesRec(l, l[0]) == 1:
        return [l[0]] + elementosDistintosRec(l[1:], e)
    return elementosDistintosRec(l[1:], e)
