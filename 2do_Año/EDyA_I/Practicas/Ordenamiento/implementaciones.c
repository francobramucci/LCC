#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CANT 10

int binsearch_rec(int a[], int len, int v) {
    int m = len / 2;
    if (len == 0)
        return -1;
    if (v == a[m])
        return m;
    if (v < a[m])
        return binsearch_rec(a, m, v);
    else {
        int resultado = binsearch_rec(a + (m + 1), len - (m + 1), v);
        return resultado == -1 ? -1 : resultado + (m + 1);
    }
}

int binsearch_it(int a[], int len, int v) {
    int ini = 0;
    int fin = len - 1;
    int m = (fin - ini) / 2;

    while (a[m] != v && fin > ini) {
        if (v > a[m])
            ini = m + 1;
        else
            fin = m - 1;
        m = ini + (fin - ini) / 2;
    }

    return a[m] == v ? m : -1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int a[], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = i; j > 1; j--) {
            if (a[j - 1] > a[j])
                swap(&a[j - 1], &a[j]);
        }
    }
}

void insertion_sort_optimizado(int a[], int len) {
    for (int i = 0; i < len; i++) {
        int temp = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > temp) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}

int *mezclar(int *arr1, int len1, int *arr2, int len2) {
    int *combinacion = malloc(sizeof(int) * (len1 + len2));
    int i = 0;
    int cont1 = 0;
    int cont2 = 0;

    while (cont1 < len1 && cont2 < len2) {
        if (arr1[cont1] < arr2[cont2])
            combinacion[i++] = arr1[cont1++];
        else
            combinacion[i++] = arr2[cont2++];
    }
    while (cont1 < len1)
        combinacion[i++] = arr1[cont1++];
    while (cont2 < len2)
        combinacion[i++] = arr2[cont2++];

    free(arr1);
    free(arr2);
    return combinacion;
}
int *mergesort(int a[], int len) {
    if (len < 2) {
        int *r = malloc(sizeof(int));
        *r = a[0];
        return r;
    } else {
        int m = len / 2;
        return mezclar(mergesort(a, m), m, mergesort(a + m, len - m), len - m);
    }
}

int particionado_lomuto(int a[], int len, int pivot) {
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (a[i] < pivot) {
            if (i != j)
                swap(a + i, a + j);
            j++;
        }
    }
    return j;
}
void quicksort(int a[], int len) {
    if (len < 2)
        return;
    int pivot = a[len - 1];
    int frontera = particionado_lomuto(a, len - 1, pivot);
    swap(a + frontera, a + (len - 1));
    quicksort(a, frontera);
    quicksort(a + frontera + 1, len - frontera - 1);
}

int *particionado2(int a[], int len, int pivot) {
    int menoresQuePivot = 0;
    int mayoresQuePivot = len;
    int *puntosDeParticion = malloc(sizeof(int) * 2);
    int i = 0;

    while (i < mayoresQuePivot) {
        if (a[i] < pivot) {
            swap(&a[i], &a[menoresQuePivot]);
            menoresQuePivot++;
            i++;
        } else if (a[i] > pivot) {
            mayoresQuePivot--;
            swap(&a[i], &a[mayoresQuePivot]);
        } else {
            i++;
        }
    }
    puntosDeParticion[0] = menoresQuePivot;
    puntosDeParticion[1] = mayoresQuePivot;
    return puntosDeParticion;
}

void quicksort2(int a[], int len) {
    if (len < 2)
        return;
    int pivot = a[len - 1];
    int *puntosDeParticion = particionado2(a, len, pivot);

    int menoresQuePivot = puntosDeParticion[0];
    int mayoresQuePivot = puntosDeParticion[1];

    free(puntosDeParticion);

    quicksort2(a, menoresQuePivot);
    quicksort2(a + mayoresQuePivot, len - mayoresQuePivot);
}

int main() {
    srand(time(NULL));
    int a[CANT];
    int b[CANT];

    for (int i = 0; i < CANT; i++) {
        a[i] = 1 + rand() % 10;
        b[i] = a[i];
    }

    insertion_sort_optimizado(a, CANT);

    for (int i = 0; i < CANT; i++) {
        printf(" %d", a[i]);
    }

    puts("");

    quicksort(b, CANT);
    for (int i = 0; i < CANT; i++) {
        printf(" %d", b[i]);
    }

    puts("");

    return 0;
}
