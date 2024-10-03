import sys

def cargarDatos(p: str) -> dict:
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

def guardarDatos(d: dict, p: str):
    with open(p, "w+") as f:
        for key, value in d.items():
            pair = key + ', ' + value + '\n'
            f.write(pair)

def main(p1, p2):
    dict_from_file = cargarDatos(p1)
    guardarDatos(dict_from_file, p2)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Provide input and output file.")
        exit()
    main(sys.argv[1], sys.argv[2])
