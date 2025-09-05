#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef void *(*FuncionCopiadora)(void *);
typedef void (*FuncionDestructora)(void *);

typedef struct {
        void **arr;
        int ultimo;
        int capacidad;
        FuncionCopiadora copiar;
        FuncionDestructora destruir;
} Vector;

/**
 * Crea un vector generico dada la capacidad y funciones para copiar y destruir.
 */
Vector *vector_crear(int capacidad, FuncionCopiadora copiar, FuncionDestructora destruir);

/**
 * Inserta un elemento al vector.
 */
void vector_insertar(Vector *vec, void *dato);

/**
 * Destruye al vector y todos los datos almacenados.
 */
void vector_destruir(Vector *vec);

/**
 * Elimina el ultimo elemento del vector y lo destruye.
 */
void vector_eliminar_ultimo(Vector *vec);

/**
 * Devuelve si el vector es vacio o no.
 */
int vector_es_vacio(Vector *vec);

/**
 * Accede al elemento en la posicion indice.
 */
void *vector_acceder(Vector *vec, int indice);

/**
 * Devuelve la cantidad de elementos presentes en el vector.
 */
int vector_cant_elementos(Vector *vec);

#endif // !__VECTOR_H__
