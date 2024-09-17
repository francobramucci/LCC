#1
# Representamos el puntaje como enteros. Los colores como strings.
# puntaje_alien : String -> Int
# La función recibe un color y en base a esto devuelve el puntaje correspondiente
# Ejemplo:
# Entrada: "verde". Salida: 5
def puntaje_alien(color):
    if color == "verde":
        puntos = 5
    if color == "amarillo":
        puntos = 10
    if color == "rojo":
        puntos = 15
    else:
        puntos = 0
    
    return puntos

#2

def regis_ent():
    tipo_ent0 = 0
    tipo_ent1 = 0
    tipo_ent2 = 0
    edad_ent = int(input("Ingrese la edad: "))
    while edad_ent != -1:
        if edad_ent < 4:
            tipo_ent0 += 1
        elif edad_ent >= 4 and edad_ent <=18:
            tipo_ent1 += 1
        elif edad_ent > 18:
            tipo_ent2 += 1 
        edad_ent = int(input("Ingrese la edad"))
    print("Se vendieron ", tipo_ent0, "entradas de tipo 0")
    print("Se vendieron ", tipo_ent1, "entradas de tipo 1")
    print("Se vendieron ", tipo_ent2, "entradas de tipo 2")
    ventotal = tipo_ent1 * 2500 + tipo_ent2 + 4000
    print("Se recadó ", ventotal)
    if tipo_ent0 > tipo_ent1 and tipo_ent0 > tipo_ent2:
        print("El tipo de entrada mas vendida es la tipo 0")
    elif tipo_ent1 > tipo_ent2 and tipo_ent1 > tipo_ent2:
        print ("El tipo de entrada mas vendida es la tipo 1")
    else:
        ("El tipo de entrada mas vendida es la tipo 2")
































































































































































































































































 
        