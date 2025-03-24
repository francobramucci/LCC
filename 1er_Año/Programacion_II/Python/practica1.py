#1
def pares25(n=25):
    if n > 1:
        print(2*n)
        pares(n-1)
    else:
        print(2)

#2.1
def pares100(n=100):
    if n > 1:
        print(2*n)
        pares(n-1)
    else:
        print(2)

#2.2
def pares(n):
    if n > 1:
        print(n*2)
        pares(n-1)
    else: 
        print(2)


#3
def paresmasq(n,m):
    if n > 1:
        if m%2== 0:
            m=m+2
        else:
            m=m+1
        print(m)
        paresmasq(n-1,m)
    else:
        print(m+2) 

#4
def sumf50(n=50):
    if n == 0:
        return 0
    return n + sumf50(n-1)

#5 
def sumallnat(n):
    if n == 0:
        return 0
    return sumallnat(n-1) + n

#6
def sumabetw(n,m):
    if m == n:
        return m
    else:
        return sumabetw(n,m-1) + m

#7
def duplica(name):
    return name*2

#8
def repeat(name,n):
    return name*n

#9
def suma(x,y):
    return x+y

def resta(x,y):
    return suma(x,-y)

def producto(x,y):
    return x*y

def cociente(x,y):
    return x/y

def calcu():
    op = int(input("1.Suma\n2.Resta\n3.Multiplica\n4.Divide\n5.Salir\n"))
    if op == 5: return
    x = int(input("Ingrese x: "))
    y = int(input("Ingrese y: "))
    if op == 1: print(suma(x,y))
    if op == 2: print(resta(x,y))
    if op == 3: print(producto(x,y))
    if op == 4: print(cociente(x,y))
    calcu()

