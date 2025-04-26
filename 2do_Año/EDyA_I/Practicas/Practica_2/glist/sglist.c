#include "sglist.h"
#include "glist.h"

SGList sglist_crear() { return NULL; }

void sglist_destruir(SGList lista, FuncionDestructora destroy) { glist_destruir(lista, destroy); }

int sglist_vacia(SGList lista) { return glist_vacia(lista); }

void sglist_recorrer(SGList lista, FuncionVisitante visit) { glist_recorrer(lista, visit); }

SGList sglist_insertar(SGList lista, void *dato, FuncionCopia copy, FuncionComparadora comp) { if (comp(dato, lista->data)) }
