from src.python.resolvedor import *

def main():
    solucion = False
    ejecutable_c = ["./build/main", "EntradaLaberinto.txt"]
    salidaC = generar_laberinto(ejecutable_c)
    primera_ejecucion = True
    if not salidaC:
        print("Error con el archivo de entrada. Se debe respetar el formato y las condiciones necesarias.")
        return
    while(not solucion):
        if not primera_ejecucion:
            generar_laberinto(ejecutable_c)
        primera_ejecucion = False
        archivoLaberinto = abrir_archivo("SalidaLaberinto.txt", "r")
        dimension = obtener_dimension(archivoLaberinto)
        laberinto = inicializar_laberinto(dimension)
        obtener_laberinto(archivoLaberinto, laberinto)
        solucion = resolver(laberinto)
        if(solucion):
            camino = encontrar_camino(laberinto)
            imprimir_lista(camino)
        archivoLaberinto.close()

if __name__ == "__main__":
    main()

