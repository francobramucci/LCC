#ifndef __AVL_H__
#define __AVL_H__

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
    AVL_RECORRIDO_IN,  /** Inorden */
    AVL_RECORRIDO_PRE, /** Preorden */
    AVL_RECORRIDO_POST /** Postorden */
} AVLRecorrido;

typedef struct _AVL *AVL;
typedef struct _AVL_Nodo AVL_Nodo;
/**
 * Retorna un arbol AVL vacio
 */
AVL avl_crear(FuncionCopiadora, FuncionComparadora, FuncionDestructora);

/**
 * Destruye el arbol y sus datos.
 */
void avl_destruir(AVL);

/**
 * Retorna 1 si el dato se encuentra y 0 en caso contrario
 */
int avl_buscar(AVL, void *);

static int avl_nodo_altura(AVL_Nodo *raiz);

static unsigned int avl_nodo_max_altura_hijos(AVL_Nodo *raiz);

static int avl_nodo_factor_balance(AVL_Nodo *raiz);

static AVL_Nodo *avl_nodo_rotacion_simple_izq(AVL_Nodo *raiz);

static AVL_Nodo *avl_nodo_rotacion_simple_der(AVL_Nodo *raiz);

static AVL_Nodo *avl_nodo_crear(void *dato, FuncionCopiadora copia);

static AVL_Nodo *avl_nodo_rebalancear(AVL_Nodo *raiz);

static AVL_Nodo *avl_nodo_insertar(AVL_Nodo *raiz, void *dato, FuncionCopiadora copia, FuncionComparadora comp);

void avl_insertar(AVL arbol, void *dato);

static int avl_nodo_validar_abb(AVL_Nodo *raiz, void *min, void *max, FuncionComparadora comp);

static int avl_nodo_validar_altura_y_balance(AVL_Nodo *raiz);

static void avl_nodo_recorrer(AVL_Nodo *raiz, AVLRecorrido orden, FuncionVisitanteExtra visita, void *extra);

/**
 * Inserta un dato no repetido en el arbol, manteniendo la propiedad de los
 * arboles AVL.
 */
void avl_insertar(AVL, void *);

/**
 * Retorna 1 si el arbol cumple la propiedad de los arboles AVL, y 0 en caso
 * contrario.
 */
int avl_validar(AVL);

/**
 * Recorrido DSF del arbol
 */
void avl_recorrer(AVL, AVLRecorrido, FuncionVisitanteExtra, void *);

AVL_Nodo *avl_pop_nodo_minimo(AVL_Nodo *raiz, void **punteroMinimoValor);

AVL_Nodo *avl_eliminar_nodo(AVL_Nodo *raiz, void *dato, FuncionComparadora comp, FuncionDestructora destroy);

void avl_eliminar(AVL arbol, void *dato);

#endif /* __AVL_H__*/
