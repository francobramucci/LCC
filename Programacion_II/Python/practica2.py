#1
def ciclo(n,m):
    for i in range(n,m+1):
        print(i)

#2
def domino():
    for i in range(7):
        for j in range(i,7):
            print("|", i, "|", j,"|")

#3 
def ndomino(n):
    for i in range(n+1):
        for j in range(i,n+1):
            print("|", i, "|", j,"|")

#4
def fact(n):
    if n == 0: return 1
    return fact(n-1)*n

def inputfact(m):
    for i in range(m):
        n = int(input("Ingrese: "))
        print(fact(n))

def fahrtocelcius():
    for i in range(0,120,10):
        r = (i-32)*5/9
        print("Fahrenheit: ", i, "\tCelsius: ", r)
        