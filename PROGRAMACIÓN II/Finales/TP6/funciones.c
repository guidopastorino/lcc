#include "funciones.h"


int randomNum(int min, int max){
    return rand() % (max - min + 1) + min;
}


FILE *abrirArchivo(const char *archivo, const char *modo){
    FILE *fp = fopen(archivo, modo);
    if(fp == NULL){
        printf("Error al abrir el archivo %s\n", archivo);
        exit(EXIT_FAILURE);
    }
    return fp;
}


void seleccionarPalabras(FILE *archivoDiccionario, int n, char ***palabras, int *cantidadPalabras){
    char palabra[50];

    while(fgets(palabra, sizeof(palabra), archivoDiccionario) != NULL){
        palabra[strcspn(palabra, "\n")] = 0;

        if(strlen(palabra) > n){
            printf("La palabra \'%s\' excede el tamaño del tablero\n", palabra);
            continue;
        } else {
            (*cantidadPalabras)++;
            *palabras = (char**)realloc(*palabras, sizeof(char**) * (*cantidadPalabras));
            (*palabras)[(*cantidadPalabras) - 1] = strdup(palabra);
        }
    }
}


void seleccionarPalabrasConPosicion(char **palabras, int cantidadPalabras, FILE *archivoSalida){
    for(int i = cantidadPalabras - 1; i > 0; i--){
        int j = randomNum(0, i);

        char *temp = palabras[i];
        palabras[i] = palabras[j];
        palabras[j] = temp;
    }

    fprintf(archivoSalida, "VERTICAL\n");

    for(int i = 0; i<cantidadPalabras; i++){
        fprintf(archivoSalida, "%s\n", palabras[i]);

        if(i == cantidadPalabras / 2 - 1){
            fprintf(archivoSalida, "HORIZONTAL\n");
        }
    }
}


void gestionarInformacionTablero(FILE *archivoDiccionario, FILE *archivoSalida){
    int n = randomNum(5, 15);

    char **palabras = NULL;
    int cantidadPalabras = 0;

    seleccionarPalabras(archivoDiccionario, n, &palabras, &cantidadPalabras);

    fprintf(archivoSalida, "%d\n", n);

    seleccionarPalabrasConPosicion(palabras, cantidadPalabras, archivoSalida);


    for(int i = 0; i<cantidadPalabras; i++){
        free(palabras[i]);
    }

    free(palabras);
}