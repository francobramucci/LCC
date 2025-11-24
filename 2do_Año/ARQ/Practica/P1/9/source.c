#include <stdio.h>

int main() {
    int A = 200, B = 300, C = 500, D = 400;
    int S = A * B * C * D;

    printf("Usando int: S = %d\n", S);
    /*
     * El resultado es ~ 10^10 > 2^31 - 1 por lo que excede el rango de int. El
     * resultado que se muestra en pantalla es negativo ya que el bit 32 se
     * encuentra encendido.
     */

    long int A1 = 200, B1 = 300, C1 = 500, D1 = 400;
    long int S1 = A1 * B1 * C1 * D1;

    printf("Usando long int: S = %ld\n", S1);
    /*
     * Al usar long int se extiende el rango a 2^63 - 1, por lo que ahora el
     * resultado puede ser almacenado correctamente y se muestra en pantalla.
     */
}
