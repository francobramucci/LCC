import sys
def main(p, s):
    f = open(p, "r")
    counter = 0

    for l in f:
        for e in l:
            if e == s[counter]:
                counter +=1
            else:
                counter = 0
            if counter == len(s):
                print(l)
                counter = 0

if __name__ == "__main__": 
    if len(sys.argv) != 3:
        print("Ingrese el archivo a leer: ")
        exit()
    main(sys.argv[1], sys.argv[2])
