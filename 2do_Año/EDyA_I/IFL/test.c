#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *copiar_substring(const char *str, int ini, int fin) {
    if (ini < 0 || fin < ini) {
        return NULL; // invalid range
    }

    int largo = fin - ini; // inclusive
    char *copy = malloc(largo + 1);
    if (!copy) {
        perror("Error reservando memoria en copiar_substring");
        exit(EXIT_FAILURE);
    }

    strncpy(copy, str + ini, largo);
    copy[largo] = '\0'; // ensure null-termination

    return copy;
}

int main() {
    char *a = "holanda";

    printf("%s", copiar_substring(a, 0, 3));
}
