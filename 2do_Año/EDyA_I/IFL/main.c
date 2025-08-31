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
    parsear_expresion("defl L1 = [2,0,4];", tablaListas, tablaFunciones);
    parsear_expresion("defl L2 = [7,0,5];", tablaListas, tablaFunciones);
    parsear_expresion("defl L3 = [7,2,1];", tablaListas, tablaFunciones);
    parsear_expresion("defl L4 = [12,2,2];", tablaListas, tablaFunciones);
    parsear_expresion("deff Md = Od <Sd> Di;", tablaListas, tablaFunciones);
    parsear_expresion("deff Mi = Oi <Si> Dd;", tablaListas, tablaFunciones);
    parsear_expresion("deff Ddi = Od <Sd> Mi;", tablaListas, tablaFunciones);
    parsear_expresion("deff S = Md Oi Mi Oi <Si Md Md Si Mi Mi> Dd Di Md;", tablaListas, tablaFunciones);
    parsear_expresion("search{L1,L2};", tablaListas, tablaFunciones);
    int exit = 0;

    // while (!exit) {
    //     char buffer[1000];
    //     printf("\n> ");
    //     scanf(" %[^\n]", buffer);
    //     if (!strcmp(buffer, "exit"))
    //         exit = 1;
    //
    //     parsear_expresion(buffer, tablaListas, tablaFunciones);
    // }

    thash_destruir(tablaListas);
    thash_destruir(tablaFunciones);

    return 0;
}
