#include <stdio.h>

int intercambiar(unsigned int x) {
    return (x >> 16) + (x << 16);
}

int main() {
    printf("El intercambio es: %d", intercambiar(1));

    return 0;
}
