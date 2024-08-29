#1
def pares(n):
    if n > 1:
        print(n*2)
        pares(n-1)
    else: 
        print(2)

# pares(25)
# pares(5)

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

#paresmasq(5,5)

#4 y 5 
def sumallnat(n):
    if n == 0:
        return 0
    else:
        return sumallnat(n-1) + n

#print(sumallnat(50))

#6
def sumabetw(n,m):
    if m == n:
        return m
    else:
        return sumabetw(n,m-1) + m
        
#print(sumabetw(10,15))

#7
def duplica(name):
    return name*2

print(duplica("Federico"))

#8
def repeat(name,n):
    return name*n

print(repeat("Perey", 12))

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


calcu()