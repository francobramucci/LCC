#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Ejercicio 1
typedef struct _punto{
    double x;
    double y;
} punto;

// par->a = (*par).a

double proy(punto p, char eje){
    if(eje == 'x' || eje == 'y') return (eje == 'x') ? p.x : p.y;
}

double dist(punto p1, punto p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

char pos(punto p){
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
    cp = "abc";
    ip1 = (int*)"cadena de ejemplo"; // Almaceno la dirección de la cadena en un puntero int.
    
    printf("Direccion a la que apunta cp: %p\n", cp);
    printf("Formateo cp como string: %s\n", cp);
    printf("Accedo al primer elemento de cp: %c\n", *cp); // Devuelve un char
    printf("Accedo al segundo elemento de cp: %c\n", cp[1]); // Devuelve un char
    printf("Direccion a la que apunta ip1: %p\n", ip1);
    printf("Formateo ip como int: %d\n", *ip1);
    // El primer bloque de 4096, comenzado en 0 está prohibido
    cp = 0; // Valido
    printf("cp = %p, *cp = error\n", cp);
    ip1 = 0; // Valido
    //cp = &'a'; // Error no es valido ya que el caracter 'a' no esta almacenado en memoria. Es un valor intrinseco.
    cp = &"abc"; // Las cadenas se almacenan en un espacio de memoria donde no es posible modificarlas pero si leerlas.
    printf("La direccion de memoria de cp es: %p\n", cp);
    // Luego los arrays se almacenan en otra parte de la memoria donde se puede escribir.
    //*cp = 'z'; No es posible
    ip1 = ip2; // Hacemos que ip1 apunte a la dirección de memoria igual al entero ip2 (ip2 almacena basura)
    printf("El valor de ip2 es: %d\n", ip2);
    printf("El valor de ip1 es: %p\n", ip1); // El entero ip2 pasado a hexadecimal.
    //printf("El valor de *ip1 es: %d\n", *ip1); Se intenta leer una dirección de memoria no valida
    cp = '\0'; // Valido, se le asigna 0
    printf("El valor de cp es: %d\n", cp);
    ip1 = '\0'; // Valido, se le asigna 0
    printf("El valor de ip1 es: %d\n", ip1);
    cp = &ch; // Valido
    //*ip1 = ip2; Estamos tratando de modificar memoria en el bloque 0.
    int i = 77, j = 100; ip1 = &i;
    *ip1 = j;
    printf("Valor de ip1: %d\n", *ip1);
}

// Ejercicio 4
// 1
void initialize(int* a, int* b) {
    if (*a >0) *b = 1; else *b = 0;
}

int main1() {
    int a = -10, b = 20;
    initialize(&a, &b);
    printf (" %d %d \n", a, b);
    return 0;
}

// 2
int main2() {
    int *pi = malloc(sizeof(int));
    int *pj = malloc(sizeof(int));
    *pi = 11;
    free(pj);
    pj = pi;
    printf("*pi = %d , *pj = %d ", *pi,* pj) ;
    free(pj);

    return 0;
 }

// 3
int main3(){
    int *ptr = malloc(sizeof(int)), a = 34;
    int b = 45, *ptr2 = &b;
    *ptr = 34;
    printf ("%d =?= %d\n", a, *ptr);
    return 0;
}

// 4
struct vector{
    float x, y;
};

struct vector* normal(struct vector v){
    struct vector* ptr = malloc(sizeof(struct vector));
    ptr->x = v.y;
    ptr->y = - v.x;
    return ptr ;
 }


// Ejercicio 5
void ej_5(){
    struct estudiante {
        char *apellido;
        int anio_ingreso;
        char division;
    };

    struct estudiante nuevo, *pest = &nuevo ;
    nuevo.apellido = "Lopez";
    nuevo.anio_ingreso = 1998;
    nuevo.division = 'A';

    //a. nuevo->apellido - Invalido
    //b. pest->division - Valido
    //(*pest)->apellido - Invalido
    //d. *pest->apellido - Invalido
    //e. *(pest->apellido+2) - Invalido
    //f. pest->apellido[2] - Valido
}

int main(){
    // tipo_valor();
    // ej_3();
    // main2();
    // main3();
    struct vector v = {x: 10, y: 20};
    struct vector* v_normal = normal(v);
    printf("v.x = %f, v.y = %f\n", v.x, v.y);
    printf("v_normal->x: %f, v_normal->y: %f\n", v_normal->x, v_normal->y);
    ej_5();
    return 0;
}