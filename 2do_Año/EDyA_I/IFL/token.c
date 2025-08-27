#include "token.h"

Token *crear_token() {
    Token *token = malloc(sizeof(Token));
    token->type = 0;
    token->value = NULL;

    return token;
}

void actualizar_token(TokenType type, char *value, Token *token) {
    free(token->value);
    token->type = type;
    token->value = value;
}

void liberar_token(Token *token) {
    if (token) {
        free(token->value);
        free(token);
    }
}
