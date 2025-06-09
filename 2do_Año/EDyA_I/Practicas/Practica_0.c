#include <stdio.h>
#include <stdlib.h>

// 1
void imprimir_direcciones() {
    int x;
    printf("La direccion de x es: %p\n", &x);

    char arr[10];
    for (int i = 0; i < 9; i++) {
        printf("Direccion de arr: %p\n", arr);
        printf("Direccion del elemento %i: %p\n", i, &arr[i]);
    }
}

// 2
/*
 * Se modifica el primer elemento ya que el array es pasado por referencia a la funcion.
 * Esto significa que se obtiene la direccion de memoria en donde se almacenan los elementos
 * del array y se escribe en esa direccion el elemento 0.
 * La función en realidad es llamada por valor, en el sentido que se pasa el valor de la referencia del array.
 */
void set_first(int a[]) {
    a[0] = 0;
}

// 3
void set_in(int *a) {
    if (*a == 0)
        *a = 1;
    else
        *a = 0;
}

// 4

int main() {
    // imprimir_direcciones();

    int a[10] = {1, 2, 3};

    printf("El primer elemento es: %i\n", a[0]);
    set_first(a);
    printf("Ahora el primer elemento es: %i\n", a[0]);

    return 0;
}
