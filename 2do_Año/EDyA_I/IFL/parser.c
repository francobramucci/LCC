#include "parser.h"
#include "dlist.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int caracter_valido(char c) {
    return isalnum(c) || c == '_';
}

char *strip(char *cadena) {
    int i = 0, ultimoEspacio = -1, actualizarPos = 1;
    while (isspace(*cadena))
        cadena += 1;
    while (cadena[i] != '\0') {
        if (isspace(cadena[i]) && actualizarPos == 1) {
            ultimoEspacio = i;
            actualizarPos = 0;
        }
        if (!isspace(cadena[i])) {
            ultimoEspacio = -1;
            actualizarPos = 1;
        }
        i++;
    }
    if (ultimoEspacio != -1)
        cadena[ultimoEspacio] = '\0';
    return cadena;
}

int validar_identificador(char *identificador) {
    while (*identificador != '\0' && caracter_valido(*identificador)) {
        identificador++;
    }
    return (*identificador == '\0');
}

typedef enum {
    EST_INICIO,
    EST_ANTES_NUMERO,
    EST_NUMERO,
    EST_ESPACIO_POST_NUMERO,
    EST_DESPUES_COMA,
    EST_FIN,
    EST_ERROR
} Estado;

int validar_lista(const char *lista) {
    Estado estado = EST_INICIO;

    for (int i = 0; lista[i] != '\0' && estado != EST_ERROR; i++) {
        char c = lista[i];

        switch (estado) {
        case EST_INICIO:
            if (isspace(c))
                continue;
            estado = (c == '[') ? EST_ANTES_NUMERO : EST_ERROR;
            break;

        case EST_ANTES_NUMERO:
            if (isspace(c))
                continue;
            if (c == ']')
                estado = EST_FIN;
            else
                estado = isdigit(c) ? EST_NUMERO : EST_ERROR;
            break;

        case EST_NUMERO:
            if (isdigit(c)) {
            } else if (isspace(c)) {
                estado = EST_ESPACIO_POST_NUMERO;
            } else if (c == ',') {
                estado = EST_DESPUES_COMA;
            } else if (c == ']') {
                estado = EST_FIN;
            } else {
                estado = EST_ERROR;
            }
            break;

        case EST_ESPACIO_POST_NUMERO:
            if (isspace(c)) {
            } else if (c == ',') {
                estado = EST_DESPUES_COMA;
            } else if (c == ']') {
                estado = EST_FIN;
            } else {
                estado = EST_ERROR;
            }
            break;

        case EST_DESPUES_COMA:
            if (isspace(c))
                continue;
            estado = isdigit(c) ? EST_NUMERO : EST_ERROR;
            break;

        case EST_FIN:
            estado = EST_ERROR;
            break;

        case EST_ERROR:
            break;
        }
    }
    return estado == EST_FIN;
}

DList *lista_to_intdlist(char *lista) {
    DList *dlist = dlist_crear();
    char *num = strtok(lista, "[], ");
    while (num != NULL) {
        dlist_agregar_final(dlist, atoi(num));
        num = strtok(NULL, "[], ");
    }

    return dlist;
}

int parsear_defl(char *parametros, char **idPointer, DList **dlistPointer) {
    char *id = strip(strtok(parametros, "="));
    char *lista = strtok(NULL, ";");

    if (lista == NULL) {
        printf("Entrada invalida. Debe incluirse el operador '='.");
        return 1;
    } else
        lista = strip(lista);

    if (!validar_identificador(id)) {
        printf("Entrada invalida. El identificador debe ser una sola cadena y contener solo alfanumericos o el "
               "caracter '_'.");
        return 1;
    }

    if (!validar_lista(lista)) {
        printf("Entrada invalida. Sintaxis de lista incorrecta.");
        return 1;
    }

    *idPointer = id;
    *dlistPointer = lista_to_intdlist(lista);

    return 0;
}

int validar_funcion(char *funcion) {
    char *subFuncion = strtok(funcion, " ");
    int esValido = 1;
    while (subFuncion != NULL) {
        if (!validar_identificador(subFuncion) || !find(subFuncion, tablaHash))
            esValido = 0;
        subFuncion = strtok(NULL, " ");
    }
    return esValido;
}

int validar_repeticiones(char *funcion) {
    int contadorRepeticion = 0;
    int esValido = 1;
    while (*funcion != '\0' && contadorRepeticion >= 0 && esValido) {
        char c = *funcion;
        if (c == '<') {
            if (*(funcion + 1) == '>')
                esValido = 0;
            contadorRepeticion++;
        }
        if (c == '>')
            contadorRepeticion--;
        funcion++;
    }

    return contadorRepeticion == 0 && esValido;
}

int validar_subfunciones(char *funcion) {
    char *subFuncion = funcion;
    while (subFuncion != NULL) {
        int inicioSubFuncion = strspn(subFuncion, "<> ");
        subFuncion += inicioSubFuncion;
        int finalSubFuncion = strcspn(subFuncion, "<> ");
        char temp = subFuncion[finalSubFuncion];
        subFuncion[finalSubFuncion] = '\0';
        validar_identificador(subFuncion);
        subFuncion += finalSubFuncion;
    }
}

int parsear_deff(char *parametros, char **idPointer, char **fcPointer) {
    char *id = strip(strtok(parametros, "="));
    char *funcion = strtok(NULL, ";");

    if (funcion == NULL) {
        printf("Entrada invalida. Debe incluirse el operador '='.");
        return 1;
    } else
        funcion = strip(funcion);

    if (!validar_identificador(id)) {
        printf("Entrada invalida. El identificador debe ser una sola cadena y contener solo alfanumericos o el "
               "caracter '_'.");
        return 1;
    }

    if (!validar_funcion(funcion)) {
        printf("Entrada invalida. Sintaxis de funcion incorrecta");
        return 1;
    }
}

int main() {
    while (1) {
        printf("\n> ");

        char buffer[256];
        scanf(" %[^\n]", buffer);

        if (!strchr(buffer, ';'))
            printf("Entrada invalida. Las sentencias deben terminar con ';'.");
        else {
            char *tipoDeSentencia = strtok(buffer, " \t\n");
            char *parametros = strtok(NULL, "");

            if (!strcmp(tipoDeSentencia, "defl")) {
                char *identificador;
                DList *dlist;
                parsear_defl(parametros, &identificador, &dlist);
            }

            if (!strcmp(tipoDeSentencia, "deff")) {
                char *identificador;
                char *funcion;
                parsear_deff(parametros, &identificador, &funcion);
            }

            if (!strcmp(tipoDeSentencia, "apply")) {
            }

            if (!strcmp(tipoDeSentencia, "search")) {
            }

            if (!strcmp(tipoDeSentencia, "exit"))
                return 0;
        }
    }

    return 0;
}
