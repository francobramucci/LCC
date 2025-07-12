#include "colas_array.h"

Cola *crear_cola() {
    Cola *q = malloc(sizeof(Cola));
    q->posicionAAgregar = 0;
    q->posicionAEliminar = 0;

    return q;
}

void enqueue(Cola *q, int datoAAgregar) {
    if (q->posicionAAgregar == q->posicionAEliminar || q->posicionAAgregar % N != q->posicionAEliminar % N)
        q->datos[q->posicionAAgregar++ % N] = datoAAgregar;
}

int dequeue(Cola *q) {
    if (q->posicionAAgregar != q->posicionAEliminar)
        return q->datos[q->posicionAEliminar++ % N];
}

int main() {
    Cola *q = crear_cola();

    printf("Agregando %d elementos...\n", N);
    for (int i = 0; i < N; i++) {
        enqueue(q, i + 1); // Inserta 1, 2, 3, 4, 5
    }

    printf("Intentando agregar uno más (debería fallar si estuviera bien hecho)...\n");
    enqueue(q, 999); // Esto no debería estar permitido, pero tu versión lo permite

    printf("Ahora desencolamos todo:\n");
    for (int i = 0; i < N; i++) {
        int val = dequeue(q);
        printf("Elemento %d: %d\n", i, val);
    }

    free(q);
    return 0;
}
