#include "flista.h"
#include "parser.h"

void insertar_funciones_primitivas(THash *tablaFunciones) {
    const char *funciones_primitivas[] = {"Oi", "Od", "Si", "Sd", "Di", "Dd"};

    for (int i = 0; i < 6; i++) {
        char *key = strdup(funciones_primitivas[i]);
        FLista *value = flista_crear(1);
        value->def[0] = strdup(funciones_primitivas[i]);
        value->largo = 1;

        thash_insertar(key, value, tablaFunciones);
    }
}

int main() {
    THash *tablaListas = thash_crear(1000, (FuncionDestructora)dlist_destruir);
    THash *tablaFunciones = thash_crear(1000, (FuncionDestructora)flista_destruir);
    insertar_funciones_primitivas(tablaFunciones);

    while (1) {
        char buffer[1000];
        printf("\n> ");
        scanf(" %[^\n]", buffer);

        parsear_expresion(buffer, tablaListas, tablaFunciones);
    }

    return 0;
}
