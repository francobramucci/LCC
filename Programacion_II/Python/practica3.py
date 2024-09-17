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
# recursivo
def busquedaDicotomicaRecursiva(l,s):
    def aux(l, ini, end, s): # [22,23] 0, 1, 50 
        mid = (ini+end) // 2 # mid = 0+1/2 = 0.5 
        if s == l[mid]: #l[mid] = l[1] = 22 < 50
            return True
        if ini == end: # ini = 0, end = 1, False 
            return False
        else:
            if s > l[mid]:
                return aux(l, mid+1, end, s) # aux([1,2], 0, 1, 13)
            else:
                return aux(l, ini, max(mid-1, 0), s)
    return aux(l, 0, len(l)-1, s)

# iterativo
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
    return s == l[mid]

#9
def showChars(s):
    for e in s:
        print(s)

#10
# recursivo
def contar(l, x):
    largo = len(l) - 1
    def aux(l, x, i):
        if i > largo:
            return 0
        if l[i] == x:
            return aux(l, x, i+1) + 1
        else:
            return aux(l, x, i+1)
    return aux(l, x, 0)

# iterativo
def contarIt(c, s):
    cont = 0
    for e in s:
        if c == e:
            cont += 1   
    return cont

#11
def countVowels(s):
    cont = 0
    vowels = ['a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U']
    for e in s:
        if e in vowels:
            cont += 1
    return cont

#12
    

