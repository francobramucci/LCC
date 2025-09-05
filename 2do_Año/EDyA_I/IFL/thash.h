#ifndef __THASH_H__
#define __THASH_H__
#include "vector.h"
#include <stdlib.h>

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef unsigned (*FuncionHash)(void *dato);
typedef void (*FuncionDestructora)(void *dato);

/**
 * Cada una de las entradas de la tabla hash.
 */
typedef struct _Entrada {
        char *key;
        void *valor;
        int sig;
} Entrada;

typedef struct {
        Entrada **tabla;
        int capacidad;
        int cantidadElementos;
        int tamRegionDirecciones;
        int indiceRegionColisiones;
        FuncionHash hash;
        FuncionCopiadora copiarKey;
        FuncionCopiadora copiarValor;
        FuncionDestructora destruirKey;
        FuncionDestructora destruirValor;
        FuncionComparadora compararKeys;
} THash;

/**
 * Crea e inicializa una nueva tabla de hash.
 * Reserva la memoria necesaria para la tabla y sus estructuras.
 * En esta implementación de listas mezcladas se utiliza una región de direcciones con un tamaño aproximado del 86%
 *  de la capacidad total (consultar Vitter, J.S. Implementations for Coalesced Hashing, 1982), ajustado al primo mas
 * cercano. El resto se utiliza como region de colisiones o "cellar", es decir que al producirse una colision en la
 * region de direcciones, se resuelve agregando el elemento en la region de colisiones y actualizando el campo sig en el
 * nodo donde se produjo la colision. En caso de que la region de colisiones se haya llenado entonces se continua
 * insertando el la region de direcciones. Ademas se cuenta con un indice que apunta al ultimo elemento colisionado
 * insertado.
 */
THash *thash_crear(int capacidad, FuncionHash hash, FuncionCopiadora copiarKey, FuncionCopiadora copiarValor,
                   FuncionDestructora destruirKey, FuncionDestructora destruirValor, FuncionComparadora compararKeys);

/**
 * Busca un valor en la tabla de hash asociado a una clave.
 * Calcula el índice inicial aplicando la función hash a la clave.
 * A partir de ese índice, recorre la cadena de colisiones (siguiendo los
 * punteros 'sig') y compara la clave en cada paso con la clave buscada.
 * Si encuentra una coincidencia, devuelve el valor asociado. Si la celda
 * inicial está vacía o se llega al final de la cadena (-1), la clave no
 * existe y devuelve NULL.
 */
void *thash_buscar(void *key, THash *hashTable);

/**
 * Inserta un par clave-valor en la tabla de hash.
 * Si la celda inicial está libre, inserta la nueva entrada ahí. Si hay
 * una colisión, recorre la cadena hasta el final. Luego, busca un espacio libre en la region de colisiones.
 * Una vez encontrado el espacio, enlaza la nueva entrada al final de la cadena.
 * Si la tabla está completamente llena, se invoca a thash_rehash() para
 * expandirla y se reintenta la inserción.
 */
void thash_insertar(void *key, void *value, THash *hashTable);

/**
 * Libera toda la memoria utilizada por la tabla hash.
 * Recorre cada celda de la tabla. Para cada entrada no nula,
 * primero invoca a la función destructora (proporcionada en la creación)
 * para liberar la memoria del valor. Luego, libera la memoria de la clave
 * y de la estructura de la entrada misma. Finalmente, libera el array de
 * la tabla y la estructura principal de la tabla de hash.
 */
void thash_destruir(THash *hashTable);

/**
 * Copia las referencias de todas las entradas no vacias de la tabla hash a un vector
 */
Vector *thash_elementos_a_vector(THash *tablaHash);

#endif // !__THASH_H__
