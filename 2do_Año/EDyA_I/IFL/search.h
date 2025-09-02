#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "apply.h"
#include "flista.h"
#include "utils.h"

// int probar_funcion_con_resto_de_pares(FLista *funcion, DList *listas, THash *tablaFunciones);
//
// void search(DList *listas, THash *tablaFunciones);

int podar(FLista *funcion, char *subfuncion);

// int buscar_funcion(FLista *funcion, DList *listaInput, DList *listaOutput, THash *tablaFunciones, DList
// *listaDePares);

int probar_funcion_con_resto_de_pares(FLista *funcion, Vector *listas, THash *tablaFunciones);
void search(Vector *paresDeListas, THash *tablaFunciones);
int buscar_funcion(FLista *funcion, DList *listaInput, DList *listaOutput, THash *tablaFunciones,
                   Vector *paresDeListas);
#endif // !__SEARCH_H__
