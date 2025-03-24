import sys
def main(p1, p2):
    f1 = open(p1, "r")
    f2 = open(p2, "w")

    for l in f1:
        f2.write(l)
    f1.close()
    f2.close()

if __name__ == "__main__":
    if(len(sys.argv) != 3):
        print("Ingrese el archivo a copiar y el archivo destino. ")
        exit()
    main(sys.argv[1], sys.argv[2])
    


