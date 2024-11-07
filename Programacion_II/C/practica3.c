#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Ejercicio 1
struct punto{
    double x;
    double y;
};

double proy(struct punto p, char eje){
    if(eje == 'x' || eje == 'y') return (eje == 'x') ? p.x : p.y;
}

double dist(struct punto p1, struct punto p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

char pos(struct punto p){
    if(p.x > 0 || p.y > 0) return '1';
    if(p.x < 0 || p.y > 0) return '2';
    if(p.x < 0 || p.y < 0) return '3';
    if(p.x > 0 || p.y < 0) return '4';
    return '0';
}

// Ejercicio 2

void tipo_valor(){
    int vector [5] = {10 , 20 , 30 , 40 , 50};
    int a = 3;
    int* ptr = &a;
    int* qtr = vector ;
    printf("a = %d, &a = %p, *a = error, ptr = %p\n", a, &a, ptr);
    printf("&ptr = %p, *ptr = %d, qtr = %p, &qtr = %p\n", &ptr, *ptr , qtr, &qtr);
    printf("*qtr = %d, vector = %p, &vector = %p, *vector = %d\n", *qtr, vector, &vector, *vector);
    printf("++qtr = %p, ++*qtr = %d, ++*vector = %d, *&ptr = %p\n", ++qtr, ++*qtr, ++*vector, *&ptr);
}

// Ejercicio 3

void ej_3(){
    int *ip1, ip2;
    char ch, *cp;
    
    printf("Dirección de memoria donde se guarda \"cadena de ejemplo\": %p\n", "cadena de ejemplo");
    
    cp = "cadena de ejemplo"; // Apunto a dirección donde se guarda "cadena de ejemplo".
    ip1 = (int*)"cadena de ejemplo"; // Almaceno la dirección de la cadena en un puntero int.
    
    printf("Direccion a la que apunta cp: %p\n", cp);
    printf("Formateo cp como string: %s\n", cp);
    printf("Direccion a la que apunta ip1: %p\n", ip1);
    printf("Formateo ip como int: %d\n", *ip1);
    // El primer bloque de 4096, comenzado en 0 está prohibido
    cp = 0; // Valido
    printf("cp = %p, *cp = error\n", cp);
    ip1 = 0; // Valido
    // cp = 'abc';
}

int main(){
    // tipo_valor();
    ej_3();


    return 0;
}