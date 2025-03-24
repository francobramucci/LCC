from random import *
#1
#a
def ocurrencias(l,e):
    cont = 0
    for x in l:
        if x == e:
            cont += 1
    return cont

#b
def primera(l,e):
    pos = -1
    flag = 0
    for i in range(len(l)):
        if e == l[i] and flag == 0:
            pos = i
            flag = 1
    return pos

#c
def posiciones(l, e, add):
    first = primera(l,e)
    if first == -1:
        return []
    add += first
    return [first+add] + posiciones(l[first:], e, add)

#2
#a) 
def vmax(l):
    if  l == []:
        return 0
    elif len(l) == 1:
        return l[0]
    elif l[0] < l[1]:
        return vmax(l[1:])
    else:
        return vmax(l[0]+l[2:])
    
#b)
def pos(l):
    num = l[0]
    posi = 0
    for i in range(1,len(l)):
        if num < l[i]:
            num = l[i]
            posi = i
    return (num, posi)

#3
def binarySearchIterativa(l,s):
    ini = 0
    end = len(l)-1
    mid = (ini+end) // 2
    while end-ini >= 0 and l[mid] != s:
        mid = (ini+end) // 2
        if s > l[mid]:
            ini = mid + 1
        else: 
            end = mid - 1
    if l[mid] == s:        
        return mid
    return -1

def buscarOinsertar(l,e):
    pos = binarySearchIterativa(l,e) 
    if pos != -1:
        return pos
    else:
        i = 0
        while(l[i] < e):
            i += 1
        l = l[:i] + [e] + l[i:]
        print(l)
        return i+1

#4
def tuplelist_to_dict(l: list) -> dict:
    a = {}
    for e in l:
        a[e[0]] = e[1]
        print(a[e[0]])
    return a

#5a
def count_string(s):
    words = s.split()
    d = {}
    for e in words:
        if e not in d.keys():
            d[e] = 1
        else:
            d[e] += 1
    return d

#5b
def count_char(s: str):
    d = {}
    for i in range(len(s)):
        if s[i] not in d.keys():
            d[s[i]] = 1
        else:
            d[s[i]] += 1
    return d

#5c
def dice_prob(n: int):
    d = {}
    for i in range(n):
        dado1 = randint(1,6)
        dado2 = randint(1,6)
        suma = dado1 + dado2
        if suma not in d.keys():
            d[suma] = 1
        else:
            d[suma] += 1

#6
def larger_string(s):
    words = s.split()
    d = {}
    for i in range(len(s)):
        if s[i] not in d.keys():
            d[s[i]] = ''
    
    for e in words:
        length = len(e)
        for i in range(len(e)):
            if len(d[e[i]]) < length:
                d[e[i]] = e
    return d

#7a
def students_average(d: dict, n: str) -> int:
    suma = 0
    for e in d[n]:
        suma += e
    return suma / len(d[n])

#7b
def best_average(d: dict) -> str:
    best_note = 0
    best_student = ''
    for k in d.keys():
        ave = students_average(d, k)
        if ave > best_note:
            best_note = ave
            best_student = k
    return best_student

#8
def synonyms_replace(s: str, d: dict):
    # s.lower()
    words = s.split()
    res = []
    for e in words:
        if e in d.keys():
            synonyms = d[e]
            rand = randint(0, len(synonyms)-1) 
            res.append(synonyms[rand])
        else:
            res.append(e)
    
    return ' '.join(res)

def total_buy(prices: dict, amounts: dict):
    suma = 0
    for k in amounts.keys():
        suma += amounts[k] * prices[k]
    return suma

#10
def delete_dups(l: list) -> set:
    s = set()
    s.update(l)
    return s

#11
def string_intersection(s1, s2):
    words1 = s1.split()
    words2 = s2.split()
    a = set()
    b = set()
    a.update(words1)
    b.update(words2)

    return a&b

#12
def not_in_both(s1, s2):
    onlys1 = s1-s2
    onlys2 = s2-s1

    return onlys1|onlys2

#13
def lower_than_nth(l: list, n: int):
    l.sort()
    nth = l[n]
    s = set()
    for i in range(nth):
        if i not in l:
            s.add(i)
    return s

#14
def organizar_reunion(d: dict):
    res = set(range(1,31))
    for k in d.keys():
        s = set()
        s.update(d[k])
        res &= s
    return res 

# if __name__ == "__main__"
#   main()


        
    
            




