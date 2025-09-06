#include "parser.h"
#include "thash.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

static void imprimir_ayuda();
static void insertar_funciones_primitivas(THash *tablaFunciones);
unsigned hash(char *key);
int comparar_strings(void *str1, void *str2);

int main() {
    THash *tablaListas = thash_crear(1000, (FuncionHash)hash, retornar_puntero, retornar_puntero, liberar_puntero,
                                     (FuncionDestructora)lista_destruir, comparar_strings);
    THash *tablaFunciones = thash_crear(1000, (FuncionHash)hash, retornar_puntero, retornar_puntero, liberar_puntero,
                                        (FuncionDestructora)flista_destruir, comparar_strings);

    insertar_funciones_primitivas(tablaFunciones);

    int exit = 0;

    parsear_expresion("defl L1 = [0,1,2];", tablaListas, tablaFunciones);
    parsear_expresion("defl L2 = [1,2,3];", tablaListas, tablaFunciones);
    parsear_expresion("defl L3 = [0,0,0];", tablaListas, tablaFunciones);
    parsear_expresion("defl L4 = [1,1,1];", tablaListas, tablaFunciones);
    parsear_expresion("defl A = [0,0];", tablaListas, tablaFunciones);
    parsear_expresion("defl B = [7,0];", tablaListas, tablaFunciones);
    parsear_expresion("defl C = [3];", tablaListas, tablaFunciones);
    parsear_expresion("defl D = [10];", tablaListas, tablaFunciones);
    parsear_expresion("deff Md = Od <Sd> Di;", tablaListas, tablaFunciones);
    parsear_expresion("deff Mi = Oi <Si> Dd;", tablaListas, tablaFunciones);
    parsear_expresion("deff Ddi = Od <Sd> Mi;", tablaListas, tablaFunciones);
    parsear_expresion("deff S = Md Oi Mi Oi <Si Md Md Si Mi Mi> Dd Di Md;", tablaListas, tablaFunciones);
    parsear_expresion("search{L1,L2; L3,L4};", tablaListas, tablaFunciones);
    // // parsear_expresion("search{A,B;C,D};", tablaListas, tablaFunciones);
    // parsear_expresion("defl L5 = [23,1923,12931,2393];", tablaListas, tablaFunciones);
    printf("Interprete de funciones de listas. Escriba 'help' para obtener informacion, 'exit' para terminar la "
           "ejecucion.");
    while (!exit) {
        char buffer[1000];
        printf("\n> ");
        scanf(" %[^\n]", buffer);

        if (!strcmp(buffer, "exit"))
            exit = 1;
        else if (!strcmp(buffer, "help"))
            imprimir_ayuda();
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

static void imprimir_ayuda() {
    printf(
        "Comandos disponibles:\n\n"
        "1. defl NOMBRE_LISTA = [a0, a1, ..., an];\n"
        "   - Define una lista con nombre NOMBRE_LISTA y elementos enteros a0 ... an. Ej: defl L1 = [1,2,3];\n\n"
        "2. deff NOMBRE_FUNCION = f;\n"
        "   - Define una funcion de lista con nombre NOMBRE_FUNCION como una funcion de lista f. Ej: deff Md = Od <Sd> "
        "Di; \n\n"
        "3. apply NOMBRE_FUNCION NOMBRE_LISTA;\n"
        "   - Aplica la funcion de lista NOMBRE_FUNCION a la lista existente NOMBRE_LISTA. Ej: apply Md L1;\n\n"
        "4. apply NOMBRE_FUNCION [a0, a1, ..., an];\n"
        "   - Aplica la funcion de lista NOMBRE_FUNCION a una lista definida directamente en la linea. Ej: apply Md "
        "[1,2,3];\n\n"
        "5. search {L11,L12; L21,L22; ... Ln1,Ln2};\n"
        "   - Busca una funcion de lista que transforme cada lista Li1 en Li2 para todos los pares de listas dados. Ej "
        "search {L1,L2};\n\n"

        "Los nombres de listas y funciones deben estar compuestos por alfanumericos o el simbolo '_' ");
}

unsigned hash(char *key) {
    unsigned hashval;

    for (hashval = 0; *key != '\0'; key++) {
        hashval = *key + 67 * hashval;
    }

    return hashval;
}

int comparar_strings(void *str1, void *str2) {
    return strcmp((char *)str1, (char *)str2);
}
