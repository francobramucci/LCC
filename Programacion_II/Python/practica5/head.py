import sys

def main(s, n):
    n = int(n)
    f = open(s, 'r')
    for i in range(n):
        print(f.readline())
   f.close()

if __name__ == "__main__":
    if(len(sys.argv) != 3):
        print("Ingrese la ruta de un archivo y la cantidad de lineas a leer.")
        exit()
    else:
        main(sys.argv[1], int(sys.argv[2]))
