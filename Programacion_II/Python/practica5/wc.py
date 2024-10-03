import sys
def main(p):
    lines_counter = 0
    char_counter = 0
    word_counter = 0

    f = open(p, "r")
    fchar = f.read(1)
    
    while fchar != '':
        char_counter += 1
        if fchar == '\n':
            lines_counter += 1
        if fchar == '\n' or fchar == ' ':
            word_counter += 1
        fchar = f.read(1)

    print("Lines:", lines_counter+1, "Words:", word_counter+1, "Characters:", char_counter)
    f.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Ingrese el archivo a ser analizado: ")
        exit()
    main(sys.argv[1])