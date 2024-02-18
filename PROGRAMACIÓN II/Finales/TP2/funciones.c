#include "funciones.h"

FILE *obtenerArchivo(const char *nombre, const char *modo){
    FILE *fp = fopen(nombre, modo);

    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    return fp;
}

void construirAfinidades(char **personas, int cantidadPersonas, int afinidades_a_construir, FILE *archivoSalida){
    fprintf(archivoSalida, "Afinidades\n");

    int parGenerado[100][100];
    int afinidadesGeneradas = 0;

    while(afinidadesGeneradas < afinidades_a_construir){
        int i = rand() % cantidadPersonas;
        int j = rand() % cantidadPersonas;

        if(i != j && !parGenerado[i][j]){
            parGenerado[i][j] = 1;
            parGenerado[j][i] = 1;

            fprintf(archivoSalida, "%s, %s\n", personas[i], personas[j]);

            afinidadesGeneradas++;
        }
    }
}

void imprimirPersonasSalida(char **personas, int cantidadPersonas, FILE *archivoSalida){
    fprintf(archivoSalida, "Personas\n");
    for(int i = 0; i<cantidadPersonas; i++){
        fprintf(archivoSalida, "%s\n", personas[i]);
    }

}

void liberarMemoriaPersonas(char **personas, int cantidadPersonas){
    for(int i = 0; i<cantidadPersonas; i++){
        free(personas[i]);
    }

    free(personas);
}

void obtenerPersonas(char ***personas, int *cantidadPersonas, FILE *archivoEntrada){
    char persona[50];

    while(fgets(persona, sizeof(persona), archivoEntrada) != NULL){
        persona[strcspn(persona, "\n")] = 0;

        *personas = realloc(*personas, (strlen(persona) + 1) * sizeof(char*));

        (*personas)[(*cantidadPersonas)] = strdup(persona);

        (*cantidadPersonas)++;
    }
}

void generarAfinidades(FILE *archivoEntrada, FILE* archivoSalida){
    char **personas = NULL;
    int cantidadPersonas = 0;

    obtenerPersonas(&personas, &cantidadPersonas, archivoEntrada);

    int afinidades_a_encontrar = rand() % (cantidadPersonas - 1 + 1) + 1;
    int afinidades_a_construir = 7;

    fprintf(archivoSalida, "%d\n", afinidades_a_encontrar);

    imprimirPersonasSalida(personas, cantidadPersonas, archivoSalida);

    construirAfinidades(personas, cantidadPersonas, afinidades_a_construir, archivoSalida);

    liberarMemoriaPersonas(personas, cantidadPersonas);

}