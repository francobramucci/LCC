#1
#a
def ocurrencias(l,e):
    cont = 0
    for x in l:
        if x == e:
            cont += 1
    return cont

#b
def primera(l,e):
    pos = -1
    flag = 0
    for i in range(len(l)):
        if e == l[i] and flag == 0:
            pos = i
            flag = 1
    return pos

#c
def posiciones(l, e, add):
    first = primera(l,e)
    if first == -1:
        return []
    add += first
    return [first+add] + posiciones(l[first:], e, add)

#2
#a) 
def vmax(l):
    if  l == []:
        return 0
    elif len(l) == 1:
        return l[0]
    elif l[0] < l[1]:
        return vmax(l[1:])
    else:
        return vmax(l[0]+l[2:])
    
#b)
def pos(l):
    num = l[0]
    posi = 0
    for i in range(1,len(l)):
        if num < l[i]:
            num = l[i]
            posi = i
    return (num, posi)

#3
def binarySearchIterativa(l,s):
    ini = 0
    end = len(l)-1
    mid = (ini+end) // 2
    while end-ini >= 0 and l[mid] != s:
        mid = (ini+end) // 2
        if s > l[mid]:
            ini = mid + 1
        else: 
            end = mid - 1
    if l[mid] == s:        
        return mid
    return -1

def buscarOinsertar(l,e):
    pos = binarySearchIterativa(l,e) 
    if pos != -1:
        return pos
    else:
        i = 0
        while(l[i] < e):
            i += 1
        l = l[:i] + [e] + l[i:]
        print(l)
        return i+1

#4
def diccio(l: list[tuple]) -> dict:
    a = {}
    for e in l:
        a[e[0]] = e[1]
        print(a[e[0]])
    return a


            




