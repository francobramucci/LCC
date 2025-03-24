#include <stdio.h>
#include <stdlib.h>

// Ejercicio 4
void estado(){
    int temp;
    printf("Ingrese la temperatura del agua: ");
    scanf("%d", &temp);

    if(temp <= 0) printf("Solido");
    else if(temp < 100) printf("Liquido");
    else printf("Gaseoso");
}

// Ejercicio 5
void nota(int nota){
    if(nota >= 2 && nota <= 5) printf("insuficiente");
    if(nota == 6) printf("aprobado");
    if(nota == 7) printf("bueno");
    if(nota == 8) printf("muy bueno");
    if(nota == 9) printf("distinguido");
    if(nota == 10) printf("Sobresaliente");
}

void notaelif(int nota){
    if(nota >= 2 && nota <= 5) printf("insuficiente");
    else{
        if(nota == 6) printf("aprobado");
        else{
            if(nota == 7) printf("bueno");
            else{
                if(nota == 8) printf("muy bueno");
                else{
                    if(nota == 9) printf("distinguido");
                    else{
                        if(nota == 10) printf("sobresaliente");
                    }
                }
            }
        }
    }
    
}

// Ejercicio 7
int bisiesto(int ano){
    return (ano%400 == 0 || (ano%4 == 0 && ano%100 != 0));
}

// Ejercicio 8
// if (Edad > 64) printf("Seguridad social");
// if (Edad < 18) printf("Exento");
// else printf("Imposible");

// Ejercicio 9
void show_100(){
    int i = 0;
    while(++i && i <= 100) printf("%d ", i);
}

// Ejercicio 10
void show_odds(){
    int i = 0; 
    while(++i && i <= 100) (i % 2 == 1) ? printf("%d ", i) : i;
}

// Ejercicio 11
void numbers_between(){
    int x = 0, y = 0;

    while(x >= y){
        printf("\nIngrese los extremos de un intervalo de forma ordenada: ");
        scanf("%d %d", &x, &y);
    }
    printf("\n"); 
    while(x++ && x < y) printf("%d ", x);
}

// Ejercicio 12
void is_prime(){
    int n;
    printf("\nIngrese un numero: ");
    scanf("%d", &n);
    int i = 2;
    while(n % i != 0 && i * i <= n) i++;
    (n == 1 || (n % i == 0)) ? printf("\nEl numero no es primo") : printf("\nEl numero es primo"); 

}

// Ejercicio 13
double fact(int n){
    double fac = 1;
    while(n > 1){
        fac *= n;
        n--;
    }
    return fac;
}

// Ejercicio 14

void edad_media_pacientes(){
    int cant;
    printf("\nIngrese la cantidad de pacientes: ");
    scanf("%i", &cant);
    float cont_total = 0, cont_ingresados = 0, cont_operados = 0, cant_ingresados = 1, cant_operados = 1;

    while(cant--){
        float edad;
        float indice;
        printf("\nIngrese edad e indice: ");
        scanf("%f %f", &edad, &indice);
        if(indice > 0.6){
            if(indice > 0.9){ cont_operados += edad;  cant_operados++;}
            else{ cont_ingresados += edad; cant_ingresados++;}
        }
        cont_total += edad;
    }
    printf("Promedio total: %f. Promedio ingresados: %f. Promedio operados: %f", cont_total/(float)cant, cont_ingresados/cant_ingresados, cont_operados/cant_operados);
}

int fib(int n){
    if(n==1)
        return 1;
    else if(n==0){
        return 0;
    }
    else{
        return fib(n-1)+fib(n-2);
    }
}

int fibit(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    
    long long a = 0, b = 1; 
    int i = 2;

    while(i <= n){
        int c = b;
        b += a;
        a = c;
        i++;
    }
    return b;
}

int main(){
    /*int anio;
    printf("Ingrese el año: ");
    scanf("%d", &anio);
    printf("%d %s \n", anio, (bisiesto(anio)? "es bisiesto" : "no es bisiesto"));
    printf("El fib de 8 es %d\n", fib(8));
    int n;
    printf("Ingrese el numero: ");
    scanf("%d", &n);
    printf("%d! = %.0f \n", n, fact(n));*/

    int n;
    printf("Ingrese el numero: ");
    scanf("%d", &n);
    printf("%d! = %d\n", n, fibit(n));
    show_100();
    show_odds();
    numbers_between();
    is_prime();
    edad_media_pacientes();
    return 0;
}
