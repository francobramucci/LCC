#include "bstree.h"
/** Casos de prueba para arboles de busqueda binaria generales */

/*
 * Eliminación de un nodo en un BST:
 *
 *		10			10 \			  \
 *		  20		  25
 *		 /  \		 /  \
 *		15	25  -->	15	30
 *	      \   \		  \
 *		  16  30	  16
 *		    \			\
 *		    18			18
 *		      \			  \
 *		      19		  19
 *
 * En este caso elegimos el nodo más chico del subarbol derecho (tomando como raíz a 20)
 */

#define N_PALABRAS 16

static void *copiar_cadena(void *dato) {
    char *str = malloc(sizeof(char) * (strlen(dato) + 1));
    assert(str != NULL);
    strcpy(str, dato);
    return str;
}

static int comparar_cadena(void *dato1, void *dato2) {
    return strcmp(dato1, dato2);
}

static void destruir_cadena(void *dato) {
    free(dato);
}

static void imprimir_cadena(void *dato, __attribute__((unused)) void *extra) {
    /* __attribute__((unused)) le dice al compilador que esta variable puede no
     * ser usada, de esta forma las banderas no tiran warnings.*/
    printf("\"%s\" ", (char *)dato);
}

static void *copiar_entero(void *i) {
    int *copia = malloc(sizeof(int));
    *copia = *((int *)i);
    return copia;
}

static int comparar_entero(void *i, void *j) {
    int a = *((int *)i);
    int b = *((int *)j);
    if (a > b)
        return 1;
    if (a < b)
        return -1;
    return 0;
}

static void imprimir_entero(void *i, __attribute__((unused)) void *extra) {
    int a = *((int *)i);
    printf("%d ", a);
}

static void destruir_entero(void *i) {
    free(i);
}

int main() {
    char *palabras[N_PALABRAS] = {"gato",     "perro",    "casa",      "persona",  "parque",  "arbol",
                                  "edificio", "calle",    "argentina", "santa fe", "rosario", "unr",
                                  "edya",     "farmacia", "tiempo",    "celular"};

    // Creamos un arbol vacio y le insertamos las palabras
    BSTree arbol = bstree_crear();
    for (int i = 0; i < N_PALABRAS; i++)
        arbol = bstree_insertar(arbol, palabras[i], copiar_cadena, comparar_cadena);

    // Imprimir el arbol inorden (alfabetico)
    printf("Recorrido inorden: ");
    bstree_recorrer(arbol, BTREE_RECORRIDO_IN, imprimir_cadena, NULL);
    puts("");

    // Buscar elementos
    assert(bstree_buscar(arbol, "farmacia", comparar_cadena) == 1);
    assert(bstree_buscar(arbol, "santa fe", comparar_cadena) == 1);
    assert(bstree_buscar(arbol, "persona", comparar_cadena) == 1);
    assert(bstree_buscar(arbol, "unr", comparar_cadena) == 1);
    assert(bstree_buscar(arbol, "argentina", comparar_cadena) == 1);
    assert(bstree_buscar(arbol, "telefono", comparar_cadena) == 0);
    assert(bstree_buscar(arbol, "mail", comparar_cadena) == 0);
    assert(bstree_buscar(arbol, "parques", comparar_cadena) == 0);
    assert(bstree_buscar(arbol, "EDyA1", comparar_cadena) == 0);
    // Destruir arbol
    bstree_destruir(arbol, destruir_cadena);

    arbol = bstree_crear();

    int a = 5, b = 4, c = 7, d = 2, e = 6, f = 3;

    arbol = bstree_insertar(arbol, &a, copiar_entero, comparar_entero);
    arbol = bstree_insertar(arbol, &b, copiar_entero, comparar_entero);
    arbol = bstree_insertar(arbol, &c, copiar_entero, comparar_entero);
    arbol = bstree_insertar(arbol, &d, copiar_entero, comparar_entero);
    arbol = bstree_insertar(arbol, &e, copiar_entero, comparar_entero);
    arbol = bstree_insertar(arbol, &f, copiar_entero, comparar_entero);

    //*((int *)(arbol->izq->izq->der->dato)) = 6;
    void *u;
    bstree_recorrer(arbol, 0, imprimir_entero, u);
    int flag = bstree_validar(arbol, comparar_entero);
    printf("%s\n", flag ? "Es BST" : "No es BST");

    arbol = bstree_eliminar(arbol, &a, comparar_entero, destruir_entero);
    bstree_recorrer(arbol, 0, imprimir_entero, u);

    flag = bstree_validar(arbol, comparar_entero);
    printf("%s\n", flag ? "Es BST" : "No es BST");

    bstree_destruir(arbol, destruir_entero);

    return 0;
}
