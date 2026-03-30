#include <stdio.h>
#include <stdlib.h>

#define LEN 100000000
void sum(float *a, float *b, int len);
void sum_simd(float *a, float *b, int len);

int main() {

    float *a = malloc(sizeof(float) * LEN);

    for (int i = 0; i < LEN; i++) {
        a[i] = i;
    }

    sum_simd(a, a, LEN);

    printf("%f, %f, %f", a[1], a[500000], a[999999]);

    return 0;
}
