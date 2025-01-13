import subprocess

def generar_laberinto():
    subprocess.run(["./main", "EntradaLaberinto.txt"])

def abrir_archivo(path:str, modo:str):
    archivo = open(path, modo) 
    return archivo

def obtener_laberinto(archivo):


if __name__ == "__main__":
    generar_laberinto()
    laberinto = abrir_archivo("SalidaLaberinto.txt", "r")
