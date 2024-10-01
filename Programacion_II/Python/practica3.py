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
            return mid
        if ini == end: # ini = 0, end = 1, False 
            return -1
        else:
            if s > l[mid]:
                return aux(l, mid+1, end, s) # aux([1,2], 0, 1, 13) else:
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
    if l[mid] == s:        
        return mid
    return -1

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
def countWordsLongerThan(s):
    cont = 0
    res = 0
    for i in range(len(s)):
        if s[i] == ' ' :
            if cont > 5:
                res += 1
            cont = 0
        else:
            cont += 1        
    if cont > 5:
        res += 1
    return res

#13
#a 
# carta: (Numero, Palo)
def esPoker(c1, c2, c3, c4, c5):
    res = False
    l = [0]*12
    l[c1[0]] += 1
    l[c2[0]] += 1
    l[c3[0]] += 1
    l[c4[0]] += 1
    l[c5[0]] += 1
    for e in l:
        if e == 4:
            res = True
    return res

#14
#a
# tiempo : (Horas, Minutos, Segundos)
def sumaTiempo(t1, t2):
    segundos = t1[2] + t2[2]
    minutos = t1[1] + t2[2] + segundos // 60 
    horas = t1[0] + t2[0] + minutos // 60
    j
    return (horas, minutos % 60, segundos % 60)

#15
def diaSiguiente1(t):
    year = t[2]
    mes = t[1]
    dia = t[0]
    bisiesto = (year % 400 == 0 or (year % 4 == 0 and year % 100 != 0))
    meses_31 = [1,3,5,7,8,10,12]
    if mes == 2 and dia == 28:
        if bisiesto:
            return (dia+1, mes, year)
        return (1, mes + 1, year)
    if (mes == 2 and dia == 29) or (mes in meses_31 and dia == 31) or (mes not in meses_31 and dia == 30):
        if(mes == 12):
            return (1, 1, year + 1)
        return (1, mes + 1, year)

#16
def diaSiguiente2(t):
    meses = ["Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"]
    mes_number = meses.index(t[1]) + 1
    t_number = diaSiguiente1((t[0], mes_number, t[2]))

    return (t_number[0], meses[t_number[1] - 1], t_number[2])

#17a
def encajan(f1, f2):
    return f1[0] == f2[0] or f1[0] == f2[1] or f1[1] == f2[0] or f1[1] == f2[1]

#17b
def encajanString(s):
    l = []
    for i in range(len(s)):
        if s[i].isdigit():
            l.append(s[i])

    return encajan((l[0],l[1]), (l[2], l[3]))










