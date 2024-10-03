import sys

def cargarDatos(p: str):
    f = open(p, "r")
    d = {}
    for l in f:
        words = l.split()
        key = words[0]
        key = key[:len(key)-1]
        value = words[1]
        d[key] = value
    f.close()
    return d    

#def guardarDatos(d, p):


def main(p):
    print(cargarDatos(p))


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Ingrese el nombrde un archivo.")
        exit()
    main(sys.argv[1])
