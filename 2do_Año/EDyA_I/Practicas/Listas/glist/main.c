#include "contacto.h"
#include "glist.h"
#include "sglist.h"

int menor_enteros(int *a, int *b) {
    if (*a == *b)
        return 0;
    if (*a < *b)
        return 1;
    return -1;
}

int *copia_enteros(int *a) {
    int *copia = malloc(sizeof(int));
    *copia = *a;

    return copia;
}

void imprimir_enteros(int *i) {
    printf("%d ", *i);
}

int main() {

    GList lista = glist_crear();
    Contacto *contactos[6];
    contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
    contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
    contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
    contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
    contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
    contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);

    for (int i = 0; i < 6; ++i) {
        lista = glist_agregar_inicio(lista, contactos[i], (FuncionCopia)contacto_copia);
        contacto_destruir(contactos[i]);
    }

    printf("Lista:\n");
    glist_recorrer(lista, (FuncionVisitante)contacto_imprimir);

    printf("Lista Filtrada:\n");
    GList listaFiltradaMayorA60 = glist_filtrar(lista, (FuncionCopia)contacto_copia, (Predicado)contacto_mayor_a_60);
    glist_recorrer(listaFiltradaMayorA60, (FuncionVisitante)contacto_imprimir);

    glist_destruir(lista, (FuncionDestructora)contacto_destruir);
    glist_destruir(listaFiltradaMayorA60, (FuncionDestructora)contacto_destruir);

    SGList sglist = sglist_crear();

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    *a = 4;
    *b = 10;
    int c = 0;
    int d = 1;

    sglist = sglist_insertar(sglist, a, (FuncionCopia)copia_enteros, (FuncionComparadora)menor_enteros);
    sglist = sglist_insertar(sglist, b, (FuncionCopia)copia_enteros, (FuncionComparadora)menor_enteros);
    sglist = sglist_insertar(sglist, &c, (FuncionCopia)copia_enteros, (FuncionComparadora)menor_enteros);
    sglist_recorrer(sglist, (FuncionVisitante)imprimir_enteros);

    printf("Busqueda: %d", sglist_buscar(sglist, &d, (FuncionComparadora)menor_enteros));
    return 0;
}
