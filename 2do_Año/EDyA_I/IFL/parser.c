#include "parser.h"
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

int parsear_defl(char *parametros, char **idPointer, int **listaPointer) {
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

    // list_to_intlist(lista);

    return 0;
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
                char **identificador;
                int **lista;
                parsear_defl(parametros, identificador, lista);
            }

            if (!strcmp(tipoDeSentencia, "deff")) {
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
