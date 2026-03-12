#include <math.h>
#include <stdio.h>

int myisnan2(float f) {
    return *((unsigned *)&f) > 2139095040;
    // Donde 2139095040 = (1 << 30) + (1 << 29) + (1 << 28) + (1 << 27) + (1 << 26) + (1 << 25) + (1 << 24) + (1 << 23)
    // Comparamos con el entero sin signo que tiene todos los bits del exponente en 1. 
    // Debe ser estrictamente mayor ya que el significante tiene que ser distinto de 0 para ser NaN.
}

int main() {
    float g = 0.0;
    float f = 0.0 / g;
    printf("f: %f\n", f);
    // ADVERTENCIA : ‘ NAN ’ es una extension de GCC.
    if (f == NAN) {
        printf("Es NAN\n");
    }

    if (isnan(f)) {
        printf("isNaN dice que si\n");
    }

    if(myisnan2(f)){
        printf("myisnan2 dice que si\n");
    }

    printf("El casteo es: %d\n", *((int *)&f));
    
    /////////////////////////
    unsigned nan_uint = (1 << 31) + (1 << 30) + (1 << 29) + (1 << 28) + (1 << 27) + (1 << 26) + (1 << 25) + (1 << 24) + (1 << 23) + 1;
    float nan_float = *((float*)(&nan_uint));

    printf("nan_uint = %u, nan_float = %f\n", nan_uint, nan_float);

    if (nan_float == NAN) {
        printf("Es NAN\n");
    }

    if (isnan(nan_float)) {
        printf("isNaN dice que si\n");
    }

    if(myisnan2(nan_float)){
        printf("myisnan2 dice que si\n");
    }
    
    //////////////////////
    float h = 1.0;
    float k = h / g;

    printf("h: %f\n", k);

    if (k == INFINITY) {
        printf("Es INFINITY\n");
    }

    printf("g + k: %f\n", g + k);

    return 0;
}
