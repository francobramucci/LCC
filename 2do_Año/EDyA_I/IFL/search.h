#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "apply.h"
#include "cola.h"
#include "flista.h"
#include "utils.h"

int probar_funcion(FLista *funcion, DNodo *listas, THash *tablaFunciones);

FLista *generate(int length, int pos, int indices[], THash *tablaFunciones, DList *listas);

void search(DList *listas, THash *tablaFunciones);

int buscar_funcion(int length, int pos, THash *tablaFunciones, DList *listas, FLista *f);

#endif // !__SEARCH_H__
