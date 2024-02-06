#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

bool estaEnArray(char *persona, char *arr[], int len){
    for(int i = 0; i<len; i++){
        if(strcasecmp(persona, arr[i]) == 0){
            return true;
        }
    }
    return false;
}

void leerArchivo(char *personas[], int *cantidadPersonas, FILE* file){
    char linea[50];

    while(fgets(linea, sizeof(linea), file) != NULL){
        linea[strcspn(linea, "\n")] = 0;

        if(!estaEnArray(linea, personas, (*cantidadPersonas))){
            personas[(*cantidadPersonas)] = (char*)malloc(strlen(linea) + 1);
            strcpy(personas[(*cantidadPersonas)], linea);
            (*cantidadPersonas)++;
        }
    }
}

int numRandom(int min, int max){
    return rand() % (max - min + 1) + min;
}

void generarAfinidades(char *personas[], int cantidadPersonas, int afinidades_a_construir, FILE* file){
    int parejaFormada[100][100];
    int parejasFormadas = 0;

    while(parejasFormadas < afinidades_a_construir){
        int i = rand() % cantidadPersonas;
        int j = rand() % cantidadPersonas;

        if(i != j && !parejaFormada[i][j]){
            parejaFormada[i][j] = 1;
            parejaFormada[j][i] = 1;
            fprintf(file, "%s, %s\n", personas[i], personas[j]);
            parejasFormadas++;
        }
    }
}

int main(){
    FILE *archivoEntrada, *archivoSalida;
    archivoEntrada = fopen("entrada.txt", "r");
    archivoSalida = fopen("salida.txt", "w");

    if(archivoEntrada == NULL || archivoSalida == NULL){
        printf("Error al abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }

    int cantidadPersonas = 0;
    char *personas[100];
    int len = sizeof(personas) / sizeof(personas[0]);

    leerArchivo(personas, &cantidadPersonas, archivoEntrada);

    srand(time(NULL));

    int afinidades_a_encontrar = numRandom(1, cantidadPersonas);
    int afinidades_a_construir = numRandom((afinidades_a_encontrar + 2), (afinidades_a_encontrar + 4));

    printf("%d\n", afinidades_a_encontrar);
    printf("%d\n", afinidades_a_construir);

    fprintf(archivoSalida, "%d\n", afinidades_a_encontrar);
    fprintf(archivoSalida, "Personas\n");

    for(int i = 0; i<cantidadPersonas; i++){
        fprintf(archivoSalida, "%s\n", personas[i]);
    }

    fprintf(archivoSalida, "Afinidades\n");

    generarAfinidades(personas, cantidadPersonas, afinidades_a_construir, archivoSalida);

    for(int i = 0; i<cantidadPersonas; i++){
        free(personas[i]);
    }

    fclose(archivoEntrada);
    fclose(archivoSalida);

    return 0;
}