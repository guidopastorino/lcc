#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char dia[100];
    int horarioInicio;
    int horarioFinalizacion;
} Horarios;

typedef struct {
    char nombre[100];
    int dias;
    Horarios *horarios;
} Materia;

int estaEnArray(char materia[100], char *materias[], int len){
    for(int i = 0; i<len; i++){
        if(strcasecmp(materia, materias[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void gestionarMaterias(char *materias[], int *cantidadMaterias, FILE *archivoEntrada){
    char materia[100];

    while(fgets(materia, sizeof(materia), archivoEntrada)){
        materia[strcspn(materia, "\n")] = 0;

        if(!estaEnArray(materia, materias, (*cantidadMaterias))){
            materias[(*cantidadMaterias)] = (char*)malloc(strlen(materia) + 1);
            strcpy(materias[(*cantidadMaterias)], materia);
            (*cantidadMaterias)++;
        }
    }
}

int randNum(int min, int max){
    return rand() % (max - min + 1) + min;
}

void completarDatosMaterias(Materia datosMaterias[], char *materias[], char *diasClase[], int cantidadMaterias){
    for(int i = 0; i<cantidadMaterias; i++){
        strcpy(datosMaterias[i].nombre, materias[i]);
        datosMaterias[i].dias = randNum(1, 3);
        datosMaterias[i].horarios = (Horarios*)malloc(sizeof(Horarios) * datosMaterias[i].dias);

        int diasOcupados[5] = {0};

        for(int j = 0; j<datosMaterias[i].dias; j++){
            int diaClase;
            do {
                diaClase = rand() % 5;
            } while (diasOcupados[diaClase]);

            diasOcupados[diaClase] = 1;

            strcpy(datosMaterias[i].horarios[j].dia, diasClase[diaClase]);
            datosMaterias[i].horarios[j].horarioInicio = randNum(8, 19);
            if(datosMaterias[i].horarios[j].horarioInicio > 15){
                datosMaterias[i].horarios[j].horarioFinalizacion = 19;
            } else {
                datosMaterias[i].horarios[j].horarioFinalizacion = randNum(datosMaterias[i].horarios[j].horarioInicio, 19);
            }
        }
    }
}

void generarArchivoSalida(int cantidadAulas, Materia datosMaterias[], int cantidadMaterias, FILE* file){
    fprintf(file, "%d\n", cantidadAulas);
    for(int i = 0; i<cantidadMaterias; i++){
        fprintf(file, "%s\n", datosMaterias[i].nombre);

        for(int j = 0; j<datosMaterias[i].dias; j++){
            fprintf(file, "%s %d a %d\n", datosMaterias[i].horarios[j].dia, datosMaterias[i].horarios[j].horarioInicio, datosMaterias[i].horarios[j].horarioFinalizacion);
        }
    }
}

int main(){
    FILE *archivoEntrada, *archivoSalida;
    archivoEntrada = fopen("entradatp1.txt", "r");
    archivoSalida = fopen("salidatp1C.txt", "w");

    if(archivoEntrada == NULL || archivoSalida == NULL){
        printf("Error al abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }

    int cantidadAulas;
    fscanf(archivoEntrada, "%d", &cantidadAulas);
    fgetc(archivoEntrada);

    char *materias[100];
    int cantidadMaterias = 0;

    gestionarMaterias(materias, &cantidadMaterias, archivoEntrada);

    srand(time(NULL));

    char *diasClase[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes"};

    Materia datosMaterias[cantidadMaterias];

    completarDatosMaterias(datosMaterias, materias, diasClase, cantidadMaterias);

    generarArchivoSalida(cantidadAulas, datosMaterias, cantidadMaterias, archivoSalida);

    for(int i = 0; i<cantidadMaterias; i++){
        free(materias[i]);
    }

    fclose(archivoEntrada);
    fclose(archivoSalida);

    return 0;
}