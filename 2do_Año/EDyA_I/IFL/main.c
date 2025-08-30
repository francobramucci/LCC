#include "flista.h"
#include "parser.h"
#include <string.h>

void insertar_funciones_primitivas(THash *tablaFunciones) {
    char *funciones_primitivas[] = {"Oi", "Od", "Si", "Sd", "Di", "Dd"};

    for (int i = 0; i < 6; i++) {
        char *key = strdup(funciones_primitivas[i]);
        FLista *funcion = flista_crear(1);
        flista_insertar(funcion, strdup(funciones_primitivas[i]));

        thash_insertar(key, funcion, tablaFunciones);
    }
}

int main() {
    THash *tablaListas = thash_crear(1000, (FuncionDestructora)dlist_destruir);
    THash *tablaFunciones = thash_crear(1000, (FuncionDestructora)flista_destruir);
    insertar_funciones_primitivas(tablaFunciones);

    int exit = 0;

    while (!exit) {
        char buffer[1000];
        printf("\n> ");
        scanf(" %[^\n]", buffer);
        if (!strcmp(buffer, "exit"))
            exit = 1;

        parsear_expresion(buffer, tablaListas, tablaFunciones);
    }

    thash_destruir(tablaListas);
    thash_destruir(tablaFunciones);

    return 0;
}
