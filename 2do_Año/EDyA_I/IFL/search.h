#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "apply.h"
#include "dlist.h"
#include "flista.h"

typedef struct {
        DList *fst;
        DList *snd;
} DLPair;

void search(DLPair *listas, THash *tablaFunciones);

#endif // !__SEARCH_H__
