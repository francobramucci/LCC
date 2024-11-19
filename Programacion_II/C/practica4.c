#include <stdio.h>

// a)
// Se referencia hacia la direccion de memoria de x donde se encuentra
// almacenado un 7, luego en la linea se accede a dicha direccion
// y se guarda un 4. Salida: 4, 5.

void main1() {
    int *punt;
    int x = 7 , y = 5;
    punt = &x;
    *punt = 4;
    printf("%d %d\n", x, y);
}

// b)
// Se guarda la direccion de x en el puntero. Luego se le asigna el valor
// 4 a la variable x. Por ultimo se guarda la direccion de y en el puntero
// Por lo tanto se imprime el valor de la variable 'y' y luego el valor de x
// Salida: 5, 4.

void main2() {
    int *punt;
    int x = 7, y = 5;
    punt = &x;
    x = 4;
    punt = &y;
    printf ("%d %d\n", *punt ,x);
}

// c)
// Como x es un arreglo se referencia a su primer elemento, dicha dirección es
// almacenada en la variable puntero. Luego se guarda el valor 9 en la direccion
// de memoria del primero elemento de x. Salida: 9, 2, 3, 4, 5.

void main3() {
    int *punt, i;
    int x[] = {1, 2, 3, 4, 5};
    punt = x;
    *punt = 9;
    for (i = 0; i < 5; i++)
       printf("%d, ", x[i]);
    printf("\n");
}

// d)
// Se asigna la dirección del primer elemento del arreglo al puntero punt. Luego
// se suma 2 al puntero, por aritmetica de punteros en realidad se estan sumando
// 8 bytes. Luego se desreferencia dicha dirección, accedeciendo al tercer
// elemento, entonces se guarda el valor 9. Después se desreferencia la
// direccion de (x + 3) que, nuevamente por aritmetica de punteros implica que
// estamos accediendo a la direccion del primer elemento mas 12 bytes, es decir
// el cuarto elemento al que le asignamos el valor 7. Por último se accede a
// punt[1] que es equivalente a  *(punt + 1), es decir, al segundo elemento al
// que se le asigna el valor de 11. Salida: 1, 11, 9, 7 ,5.

void main4() {
    int *punt, i;
    int x[] = {1 , 2 , 3 , 4 , 5};
    punt = x;
    *(punt + 2) = 9;
    *(x + 3) = 7;
    punt[1] = 11;
    for (i = 0; i < 5; i++)
        printf("%d, " ,*(punt + i));
    printf("\n");
}

// e)
// Se &x[0] es la direccion de memoria del primer elemento de x. al sumarle 3 se
// obtiene la direccion de memoria del cuarto elemento. Luego se desreferencia a
// dicha direccion menos 2 es decir que se accede al 2do elemento y se guarda un
// 9. Luego se resta 4 bytes a punt y se asigna un 7 al tercer elemento. Luego
// se asigna un 11 al cuarto elemento. Salida: 1, 9, 7, 11, 5.

void main5() {
    int *punt, i;
    int x[5] = {1, 2, 3, 4, 5};
    punt = &x[0] + 3; 
    *(punt - 2) = 9;
    punt--;
    *(punt) = 7;
    punt[1] = 11;
    punt = x;
    for (i = 0; i < 5; i++)
       printf("%d , ", punt[i]);
    printf("\n");
}

// f)

void main6() {
    int v[4] = {2, 4, 5, 7}, a, *p;
    p = v + 2;
    p--;
    a = *p + *(p + 1) + *(v + 1) + p[2];
    printf("%d\n", a);
}

// g)

void aumentar(int *x , int *y , int z) {
    *x = *x + 2;
    *y = *y + 5;
    z = z + 4;
}

void main7() {
    int x, y, z;
    x = 3;
    y = 10;
    z = 15;
    aumentar(&x, &y, z);
    printf("%d %d %d\n", x, y, z);
}

// h)

void ingreseCadena(char *c) {
    fgets(c, 10, stdin);
}

void main8() {
    char *cadena = malloc(sizeof(char) * 10);
    fgets(cadena, 10, stdin);
    printf("%s \n", cadena);
    ingreseCadena(cadena);
    printf("%s \n", cadena);
    free(cadena);
}

int main(){

    main1();
    main2();
    main3();
    main4();
    main5();
    main6();
    main7();
    main8();

    return 0;
}
