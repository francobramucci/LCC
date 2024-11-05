#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Ejercicio 1 
void mostrarDado(){
    int dice;
    printf("Ingrese la cara del dado: ");
    scanf("%d", &dice);

    switch (dice) {
    case 1:
        printf("Uno\n");
        break;
    case 2:
        printf("Dos\n");
        break;
    case 3:
        printf("Tres\n");
        break;
    case 4:
        printf("Cuatro\n");
        break;
    case 5:
        printf("Cinco\n");
        break;
    case 6:
        printf("Seis\n");
        break;        
    default:
        printf("Número incorrecto\n");
        break;
    }
}

// Ejercicio 2
void mostrarHabitaciones(){
    int nHab;
    printf("1.Azul - 2.Roja - 3.Verde - 4.Rosa - 5.Gris\n");
    printf("Ingrese el numero de habitacion: ");
    scanf("%d", &nHab);

    switch (nHab) {
    case 1:
        printf("Primera planta - Camas: 2\n");
        break;
    case 2:
        printf("Primera planta - Camas: 1\n");
        break;
    case 3:
        printf("Segunda planta - Camas: 3\n");
        break;
    case 4:
        printf("Segunda planta - Camas: 2\n");
        break;
    case 5:
        printf("Tercera planta - Camas: 1\n");
        break;     
    default:
        printf("Número no asociado a habitacion\n");
        break;
    }
}

// Ejercicio 3
// 1.

double suma_f1(int n){
    double sum = 0;
    for(double i = 1; i <= n; i++) sum += 1/i;
    return sum;
}

// 2.
float suma_f2(int k){
    float suma = 0;
    for(float p = 1; p <= k; p++) suma += 1/(p*p);
    return suma;
}

// 3.
double suma_f3(int n){
    double sum = 0;
    for(double k = 1; k <= n; k++) sum += 1/pow(k,k);
    return sum;
}

// 4.
int suma_f4(int n){
    int sum = 0;
    for(int i = 2; i <= n; i++) sum += i*(i+1);
    return sum;
}

// Ejercicio 4

void ternas_pitagoricas(){
    for(int i = 0; i <= 20; i++){
        for(int j = 0; j <= 30; j++){
            for(int k = 0; k <= 40; k++) if((i*i + j*j) == k*k) printf("(%i, %i, %i)\n", i, j, k);
        }
    }
}

#define secret 8

void secreto(){
    int intentos = 16, flag = 0;

    while(intentos-- && !flag){
        int adivinanza;
        printf("Ingrese un numero: ");
        scanf("%i", &adivinanza);
        if(adivinanza == secret){
            printf("Numero adivinado\n");
            flag = 1;
        }
        if(adivinanza > secret) printf("El numero es mayor\n");
        if(adivinanza < secret) printf("El numero es menor\n");
    }

    if(!flag) printf("Número no adivinado");
}

void ej7(){
    int i = 0;
    char c = 'T';
    char b[6] = "bucle";

    for(c += 32; i < 5; i++, c--){
        b[6] = b[i+1]; 
        b[i+1] = '\0';
        printf("%s %i %c\n", b, 5-i, !(i % 2) ? c-32 : c);
        b[i+1] = b[6];
        b[6] = '\0';
    }

}

// Tomar por teclado un arreglo y un k e intercambiar los primeros k elementos por los ultimos. 

void swap_array(){
    int arr[100], aux[100], k, n;
    printf("Ingrese cantidad de elementos (n <= 100): ");
    scanf("%i", &n);
    printf("Ingrese elementos: ");
    for(int i = 0; i < n; i++){
        int v;
        scanf("%i", &v);
        arr[i] = v;
    }
    printf("Ingrese k: ");
    if(scanf("%i", &k) != 1) printf("Valor invalido\n");


    for(int i = k, j = 0; i < n; i++,j++) aux[j] = arr[i];
    for(int i = 0, j = n-k; i < k; i++,j++) aux[j] = arr[i];
    for(int i = 0; i < n; i++) printf("%i ", aux[i]);
}

// Ejercicio 8

void collatz(){
    int n = 0, cont = 0;
    printf("\nIngrese un numero >= 1: ");
    scanf("%d", &n);
    if (n < 1){ printf("Error"); return; }
    printf("\nEl valor inicial es %i\n", n);
    while(n != 1){
        n = (n % 2 == 0) ? n/2 : 3*n+1;
        printf("El siguiente valor es %i\n", n);
        cont++;
    }
    printf("Valor final %i, numero de pasos %i\n",n ,cont);

}

// Ejercicio 9

void fill_array(){
    int array[100];
    for(int i = 0; i<= 100; i++) { array[i] = i; printf("%i ", array[i]); }
}

// Ejercicio 10

void fill_even(){
    int array[50];
    for(int i = 100, j = 0; i <= 200; i += 2, j++){ array[j] = i; printf("%i ", array[j]); }
}

// Ejercicio 11
void fill_mult3(){
    int array[50];
    for(int i = 50, j = 0; i >= 1 ; i--, j++){ array[j] = 3*i; printf("%i ", array[j]); }
}

// Ejercicio 12

void search(){
    int arr[10], n, pos = -1;
    printf("\nIngrese los elementos del arreglo: ");
    for(int i = 0; i<10; i++) scanf("%d", &arr[i]);
    printf("Ingrese el numero a encontrar: ");
    scanf("%d", &n);

    for(int i = 0; i<10; i++) (arr[i] == n) ? pos = i: pos; 
    (pos == -1) ? printf("Error") : printf("El numero se encuentra en la posicion: %i\n", pos);
}

// Ejercicio 13
void sum_great30(){
    int n;
    printf("Ingrese un entero entre 5 y 100: ");
    scanf("%d", &n);
    if(n < 5 || n > 100){ printf("Error\n"); return; }
    
    int array[100], cont = 0;
    printf("Ingrese los elementos del arreglo: ");
    for(int i = 0; i < n; i++){ scanf("%d", &array[i]); cont+= array[i]; }
    printf("La suma de elementos del array es %s a 30.\n", (cont > 30) ? "mayor" : "menor");
}

// Ejercicio 14

void count_until_neg(){
    int n = 0, max = 0, maxi = 0, array[100] = { 0 };
    printf("Ingrese valores: ");
    while(n >= 0){
        scanf("%d", &n);
        array[n]++;
    }
    for(int i = 0; i <= 100; i++) if(array[i] > max){ max = array[i]; maxi = i; };
    printf("\nEl valor mas veces ingresado es %i con un total de %i veces.\n", maxi, max);
}

// Ejercicio 15
int sumaArr(int arr[100], int n){
    int cont = 0;
    for(int i = 0; i < n; i++) cont += arr[i];
    printf("La suma de los elementos del arreglo es %i.\n", cont);
    return cont;
}

// Ejercicio 16
int prodAlt(int arr[100], int n){
    int cont = 1;
    for(int i = 0; i < n; i+=2) cont *= arr[i];
    printf("El producto de los elementos de indice par es %i.\n", cont);
    return cont;
}

// Ejercicio 18
int char_in_string(char s[100], char c){
    int flag = 0;
    for(int i = 0; i < strlen(s); i++) if(s[i] == c) flag = 1;
    return flag;
}

// Ejercicio 19
int times_in_string(char s[100], char c){
    int cont = 0;
    for(int i = 0; i < strlen(s); i++) if(s[i] == c) cont++;
    return cont;
}

// Ejercicio 20
void print_reverse(){
    char s[100];
    printf("Ingrese la palabra: ");
    scanf("%s", s);
    for(int i = strlen(s)-1; i >= 0; i--) printf("%c", s[i]);
    printf("\n");
}

// Ejercicio 21
int is_capicua(char s[100]){
    int flag = 1;
    for(int i = 0, j = strlen(s)-1; j >= 0; i++, j--) if(s[i] != s[j]) flag = 0;
    return flag;
}

// Ejercicio 22
int is_pangrama(char s[100]){
    int arr[26] = { 0 }, flag = 1;
    for(int i = 0; i < strlen(s); i++) arr[s[i] - 97] = 1;
    for(int i = 0; i < 26; i++) if(arr[i] == 0) flag = 0;
    return flag;
}

// Ejercicio 23

int is_included(char s1[100], char s2[100]){
    int flag = 0;
    for(int i = 0; i <= strlen(s1)-strlen(s2); i++){
        if(s1[i] == s2[0]){
            int k = 0;
            while(s1[i+k] == s2[k] || k == strlen(s2)) k++;
            if(k == strlen(s2)) flag = 1;
        }
    }
    return flag;
}



int main(){
    // mostrarDado();
    // mostrarHabitaciones();
    // suma_f1(100);
    // suma_f2(30);
    // suma_f3(25);
    // suma_4(10);   
    // ternas_pitagoricas();
    // ej7();
    // swap_array();
    // collatz();
    // search();
    // sum_great30();
    // count_until_neg();
    // int arr[50] = {20,10,20,30,40};
    // sumaArr(arr, 5);
    // prodAlt(arr, 5);
    // printf("La letra %s en la palabra.\n", (char_in_string("hola", 'j')) ? "esta" : "no esta");
    // print_reverse();
    // printf("La palabra %s capicua.\n", (is_capicua("awaiawa")) ? "es" :  "no es");
    // printf("La palabra %s pangrama.\n", (is_pangrama("murcielago")) ? "es" :  "no es");
    printf("%i\n", is_included("holanda", "landa"));

    return 0;
}