#ifndef __CDLIST_H__
#define __CDLIST_H__

#include "slist.h"

typedef struct _CDNodo {
	int dato;
	struct _CDNodo *ant;
	struct _CDNodo *sig;

} CDNodo;

typedef CDNodo *CDList;

#endif /* __CDLIST_H__ */
