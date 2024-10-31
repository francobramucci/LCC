#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

//Ejercicio 2
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

//Ejercicio 3
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
    int intentos = 15, flag = 0;

    while(intentos >= 0 && !flag){
        int adivinanza;
        printf("Ingrese un numero: ");
        scanf("%i", &adivinanza);
        if(adivinanza == secret){
            printf("Numero adivinado\n");
            flag = 1;
        }
        if(adivinanza > secret) printf("El numero es mayor\n");
        if(adivinanza < secret) printf("El numero es menor\n");
        intentos--;
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


int main(){
    // mostrarDado();
    // mostrarHabitaciones();
    // suma_f1(100);
    // suma_f2(30);
    // suma_f3(25);
    // suma_4(10);   
    // ternas_pitagoricas();
    
    ej7();
    swap_array();

    return 0;
}