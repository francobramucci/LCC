import sys
def char_rotation(n: int)-> dict:
    d = {}
    for e in range(680):
        c = chr(e)
        if e > 96 and e < 123:
            d[c] = chr(97 + (e+n) % 26)
        else: 
            d[c] = c
    return d

def main(p1: str, p2: str, n: int):
    o = open(p1, "r")
    d = open(p2, "w+")
    map = char_rotation(n)

    ochar = o.read(1)

    while ochar != "":
        d.write(map[ochar])
        ochar = o.read(1)
    
    o.close()
    d.close()


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Input a origin and a destiny file and rotation.")
        exit()
    main(sys.argv[1], sys.argv[2], int(sys.argv[3]))