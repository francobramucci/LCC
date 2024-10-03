import sys

def main(s, n):
    n = int(n)
    f = open(s, 'r')
    for i in range(n):
        print(f.readline())

if __name__ == "__main__":
    if(len(sys.argv) != 3):
        print(sys.argv[0], sys.argv[1], sys.argv[2])
        print("Ingrese la ruta de un archivo y la cantidad de lineas a leer.")
        exit()
    else:
        main(sys.argv[1], sys.argv[2])
