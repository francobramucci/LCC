#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void estado(){
    int temp;
    printf("Ingrese la temperatura del agua: ");
    scanf("%d", &temp);

    if(temp <= 0) printf("Solido");
    else if(temp < 100) printf("Liquido");
    else printf("Gaseoso");
}

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

bool bisiesto(int ano){
    if(ano % 400 == 0) return true;
    if(ano % 4 == 1 && ano % 100 != 0) return true;
    else return false;
    // return ano%400 == 0 || ano%4 == 0 && ano%100 != 0;
}

double fact(int n){
    double fac = 1;
    while(n > 1){
        fac *= n;
        n--;
    }

    return fac;
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
    printf("%d! = %lld\n", n, fibit(n));
    return 0;
}