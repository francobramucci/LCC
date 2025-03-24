from random import *
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

#5
def fahrtocelcius():
    for i in range(0,120,10):
        r = (i-32)*5/9
        print("Fahrenheit: ", i, "\tCelsius: ", r)

#6
def ntriang(n):
    acc = 0
    for i in range(1, n+1):
        acc += i
        print(i, "-", acc)

def ntriang2(n):
    for i in range(1, n+1):
        print(i, "-", int(i*(i+1)/2))

# Para el caso de ntriang se realizan una suma en cada iteración dando
# un total de n sumas en total
# Por otro lado para ntriang2 se realiza una sumas más una multiplicación
# más una división por iteración dando un total de n sumas + n multiplicaciones
# + n divisiones.
# En conclusión, es más efectiva la primera versión.

#7
def ingresar_pos():
    while not input("Ingrese un número positivo: ").isdigit():
        print("Entrada incorrecta, ingrese un número positivo:")

#8
def ingresar_notas():
    entrada = "y"
    acc = 0
    cont = 0
    while entrada != "n":
        acc += int(input("Ingrese una nota: "))
        cont += 1
        entrada = input("Desea seguir ingresando notas? (y/n): ")
       
    return acc/cont

#9
def dosn():
    primero = int(input("Ingrese el primer número: "))
    segundo = int(input("Ingrese el segundo número: "))

    while segundo <= primero:
        segundo = int(input("Ingrese el segundo número: "))
    
    print(primero, segundo)

#10a
def dosnmult(n,m):
    for i in range(n,m,n):
        print(i)

#10b
def dosnmult_while(n,m):
    aux = n
    while aux < m:
        print(aux)
        aux += n
        
#10c
# A simple vista la solución con while parece más intuitiva

#11
def contra():
    contra = "abuelo1234"
    intentos = 3
    while intentos > 0 and input("Ingrese la contraseña: ") != contra: 
        print("Contraseña incorrecta. Intente nuevamente.")
        intentos -= 1
    if intentos > 0:
        return True
    return False

#12

# Esta es una posible forma usando listas por comprensión aún mejorable
# si pusieramos como extremo superior del range a la raíz de n
def es_primo(n):
    if n == 1:
        return False
    return len([x for x in range(2, n//2) if n % x == 0]) == 0
        
def criba():
    MAX = 1000
    arr = [0] * MAX
    arr[0] = 1
    arr[1] = 1
    for i in range(1,MAX):
        if arr[i] == 0:
            print(i)
            for j in range(2*i, MAX, i):
                arr[j] = 1
    return arr

# Esta es otra forma más rápida para números más grandes usando
# criba de eratóstenes
def es_prime(n):
    primos = criba()
    if not(primos[n]):
        return True
    return False

def primoshasta_n(n):
    for x in range(1,n+1): 
        if es_primo(x):
            print(x)

#13
def es_potencia_de_dos(n):
    while n % 2 == 0 and n != 1:
        n //= 2
    
    if n == 1:
        return True
    return False

def suma_pot_dos_entre(n, m):
    suma = 0
    for i in range(n+1, m):
        if es_potencia_de_dos(i):
            suma += i
    return suma
    
#14.1
def lanzamiento_dado():
    lanzamiento = 0
    cont = 0
    while lanzamiento != 6:
        input("Presione Enter para lanzar el dado.")
        lanzamiento = randint(1,6)
        print(lanzamiento)
        cont += 1
    print("Se ha lanzado el dado", cont, "veces antes de que salga 6.")

#14.2
def dados_coincidencia(n):
    cont = 0
    for i in range(6):
        dado1 = randint(1,6)
        dado2 = randint(1,6)
        print("Dado 1:", dado1, ", Dado 2:", dado2)
        if dado1 == dado2:
            cont += 1
    return cont

#14.3
def dice_game(n):
    cont_pesos = 0
    cont_dolares = 0

    while n > 0:
        dado = randint(1,6)
        print("Cara:", dado)
        if dado == 6:
            cont_pesos += 4
        if dado == 3:
            cont_dolares += 1
        if dado in [2,4,5]:
            cont_pesos -= 2
        n -= 1

    print("Cantidad de pesos:", cont_pesos)
    print("Cantidad de dolares:", cont_dolares)



