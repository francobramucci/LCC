#include "parser.h"

static void insertar_funciones_primitivas(THash *tablaFunciones);

int main() {
    THash *tablaListas = thash_crear(1000, (FuncionDestructora)dlist_destruir);
    THash *tablaFunciones = thash_crear(1000, (FuncionDestructora)flista_destruir);
    insertar_funciones_primitivas(tablaFunciones);

    int exit = 0;

    parsear_expresion("defl L1 = [0,1,2];", tablaListas, tablaFunciones);
    parsear_expresion("defl L2 = [1,2,3];", tablaListas, tablaFunciones);
    parsear_expresion("defl L3 = [0,0,0];", tablaListas, tablaFunciones);
    parsear_expresion("defl L4 = [1,1,1];", tablaListas, tablaFunciones);
    parsear_expresion("defl A = [0,0];", tablaListas, tablaFunciones);
    parsear_expresion("defl B = [11,0];", tablaListas, tablaFunciones);
    parsear_expresion("defl C = [3];", tablaListas, tablaFunciones);
    parsear_expresion("defl D = [14];", tablaListas, tablaFunciones);
    parsear_expresion("deff Md = Od <Sd> Di;", tablaListas, tablaFunciones);
    parsear_expresion("deff Mi = Oi <Si> Dd;", tablaListas, tablaFunciones);
    parsear_expresion("deff Ddi = Od <Sd> Mi;", tablaListas, tablaFunciones);
    parsear_expresion("deff S = Md Oi Mi Oi <Si Md Md Si Mi Mi> Dd Di Md;", tablaListas, tablaFunciones);
    parsear_expresion("search{L1,L2; L3,L4};", tablaListas, tablaFunciones);
    // parsear_expresion("search{A,B;C,D};", tablaListas, tablaFunciones);
    parsear_expresion("deff Mo = Sd Od Od Od <Md Md S Md S>;", tablaListas, tablaFunciones);
    parsear_expresion("defl L5 = [23,1923,12931,2393];", tablaListas, tablaFunciones);

    while (!exit) {
        char buffer[1000];
        printf("\n> ");
        scanf(" %[^\n]", buffer);
        if (!strcmp(buffer, "exit"))
            exit = 1;
        else
            parsear_expresion(buffer, tablaListas, tablaFunciones);
    }

    thash_destruir(tablaListas);
    thash_destruir(tablaFunciones);

    return 0;
}

static void insertar_funciones_primitivas(THash *tablaFunciones) {
    char *funciones_primitivas[] = {"Oi", "Od", "Si", "Sd", "Di", "Dd"};

    for (int i = 0; i < 6; i++) {
        char *key = copiar_string(funciones_primitivas[i]);
        FLista *funcion = flista_crear(1, retornar_puntero, liberar_puntero);
        flista_insertar(funcion, copiar_string(funciones_primitivas[i]));

        thash_insertar(key, funcion, tablaFunciones);
    }
}
