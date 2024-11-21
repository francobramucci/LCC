#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <ctype.h>

#define LARGO_MAXIMO 50

int numero_random(int num){
    srand(time(0));
    return random() % num;
}

void clear(){
    for(int i = 99; i; i--)
        printf("\n");
}

int cant_lineas(FILE* archivo){
    fseek(archivo, 0, 0);
    char linea[LARGO_MAXIMO];
    int cant_lineas = 0;
    while(fscanf(archivo, "%s\n", linea) != EOF)
        cant_lineas++; 

    return cant_lineas;
}

char* elegir_palabra(FILE* archivo, int cant_lineas){
    fseek(archivo, 0, 0);
    int linea_random = numero_random(cant_lineas);
    char linea[LARGO_MAXIMO];
    while(linea_random-- && (fscanf(archivo, "%s\n", linea) != EOF));
    char* palabra_elegida = malloc(sizeof(char) * (strlen(linea) + 1));
    strcpy(palabra_elegida, linea);

    return palabra_elegida;
}

void mostrar_palabra(char* palabra){
    for(int i = 0; palabra[i] != '\0'; i++)
        printf("%c ", palabra[i]);
}

char entrada(int* intentos){
    int c = '0';
    while(c < 97 || c > 122 || intentos[c % 26]){
        printf("Ingrese una letra: "); 
        c = tolower(scanf("%d", &c));
        if(c < 97 || c > 122 )
            printf("Ingrese un caracter valido.\n");
        if(intentos[c % 26])
            printf("Ingrese una letra que no haya ingresado");
        //clear();
    }

    return c;
}

int comprobar_letra(char letra, char* adivinanza, char* secreto){
    int acierto = 0;
    for(int i = 0; i < strlen(secreto); i++){
        if(letra == secreto[i]){
            adivinanza[i] = letra;
            acierto = 1;
        }
    }
    
    return acierto;
} 


int vs_maquina(char* secreto){
    int i = 0, largo = strlen(secreto), vidas = 7, intentos[26] = {};
    char* adivinanza = malloc(sizeof(char) * (largo+1));
    
    for(i = 0; i < largo; i++)
        adivinanza[i] = '_';
    adivinanza[i] = '\0';

    while(strcmp(adivinanza, secreto) != 0 && vidas){
        mostrar_palabra(adivinanza);
        char letra = entrada(intentos);
        printf("letra: %c", letra);
        intentos[letra % 26] = 1;
        if(!comprobar_letra(letra, adivinanza, secreto))
            vidas--;
    }

    return (vidas > 0);
}

int main(int argc, char const *argv[]){
    if(argc != 2){
        printf("Ingrese el archivo lemario.\n");
        return 1;
    }

    FILE* archivo = fopen(argv[1], "r");
    assert(archivo != NULL);
    int cant_lineas_archivo = cant_lineas(archivo);
    char* palabra_secreta = elegir_palabra(archivo, cant_lineas_archivo); 
    vs_maquina(palabra_secreta);

    free(palabra_secreta);


    return 0;
}
