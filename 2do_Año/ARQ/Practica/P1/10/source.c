#include <stdio.h>

int main() {
    {
        char a = 127;
        printf("%hhd %hhu \n", a, a);
        a++;
        printf("%hhd %hhu \n", a, a);

        unsigned char b = 128;
        printf("%hhd %hhu \n", b, b);
        b++;
        printf("%hhd %hhu \n", b, b);
    }

    {
        char a = 127;

        printf("%d %u \n", a, a);
        a++;
        printf("%d %u \n", a, a);
        /*
         * Lo que ocurre en este caso es que char por defecto es signed. Al sumarle 1 se obtiene -128. Luego printf
         * promueve el char a int y extiende el signo con 1's. Entonces, al imprimirlo interpretado como unsigned, se
         * toman todos los 1 ignorando el concepto de signo y se devuelve un número muy grande (2^32 - 128)
         */

        unsigned char b = 128;
        printf("%d %u \n", b, b);
        b++;
        printf("%d %u \n", b, b);

        /*
         * En este caso como se trata de unsigned char no ocurre la extensión de signo con 1's sino que simplemente se
         * rellena con 0's
         */
    }
    return 0;
}
