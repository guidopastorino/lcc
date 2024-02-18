#include "funciones.h"

int numRandom(int min, int max){
    return rand() % (max - min + 1) + min;
}

int estaEnArray(char ***arr, char *el, int size){
    for(int i = 0; i<size; i++){
        if(strcasecmp((*arr)[i], el) == 0){
            return 1;
        }
    }

    return 0;
}

FILE* obtenerArchivo(const char *archivo, const char *modo){
    FILE *fp = fopen(archivo, modo);

    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    return fp;
}

void generarArchivoSalida(Materia **informacionMaterias, int cantidadMaterias, int cantidadAulas, FILE *archivoSalida){
    fprintf(archivoSalida, "%d\n", cantidadAulas);

    for(int i = 0; i<cantidadMaterias; i++){
        fprintf(archivoSalida, "%s\n", informacionMaterias[i]->nombre);

        for(int j = 0; j<(informacionMaterias[i]->dias); j++){
            fprintf(archivoSalida, "%s %d a %d\n", informacionMaterias[i]->horarios[j].dia, informacionMaterias[i]->horarios[j].horarioInicio, informacionMaterias[i]->horarios[j].horarioFinalizacion);
        }
    }
}

void liberarMateriasConInformacion(Materia **informacionMaterias, int cantidadMaterias){
    for(int i = 0; i<cantidadMaterias; i++){
        free(informacionMaterias[i]->nombre);

        for(int j = 0; j<(informacionMaterias[i]->dias); j++){
            free(informacionMaterias[i]->horarios[j].dia);
        }

        free(informacionMaterias[i]->horarios);
        free(informacionMaterias[i]);
    }

    free(informacionMaterias);
}

void asignarInformacionMaterias(char **materias, int cantidadAulas, int cantidadMaterias, FILE* archivoSalida){
    char *dias[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes"};

    Materia **informacionMaterias = (Materia**)malloc(sizeof(Materia*) * cantidadMaterias);

    for(int i = 0; i<cantidadMaterias; i++){
        informacionMaterias[i] = (Materia*)malloc(sizeof(Materia));
        informacionMaterias[i]->nombre = strdup(materias[i]);
        informacionMaterias[i]->dias = numRandom(1, 3);
        informacionMaterias[i]->horarios = (Horarios*)malloc(sizeof(Horarios) * informacionMaterias[i]->dias);

        int *diasOcupados = (int*)calloc(5, sizeof(int));

        for(int j = 0; j<(informacionMaterias[i]->dias); j++){
            int indiceDia;

            do {
                indiceDia = numRandom(0, 4);
            } while(diasOcupados[indiceDia]);

            diasOcupados[indiceDia] = 1;

            informacionMaterias[i]->horarios[j].dia = strdup(dias[indiceDia]);
            informacionMaterias[i]->horarios[j].horarioInicio = numRandom(8, 19);
            if(informacionMaterias[i]->horarios[j].horarioInicio > 15){
                informacionMaterias[i]->horarios[j].horarioFinalizacion = 19;
            } else {
                informacionMaterias[i]->horarios[j].horarioFinalizacion = informacionMaterias[i]->horarios[j].horarioInicio + 4;
            }
        }

        free(diasOcupados);
    }

    generarArchivoSalida(informacionMaterias, cantidadMaterias, cantidadAulas, archivoSalida);

    // liberar memoria de informacionMaterias
    liberarMateriasConInformacion(informacionMaterias, cantidadMaterias);
}

void obtenerMaterias(char ***materias, int *cantidadMaterias, FILE *archivoEntrada){
    char materia[50];

    while(fgets(materia, sizeof(materia), archivoEntrada)){
        materia[strcspn(materia, "\n")] = 0;

        if(!estaEnArray(materias, materia, (*cantidadMaterias))){
            *materias = realloc(*materias, sizeof(char *) * (strlen(materia) + 1));

            if(*materias == NULL){
                printf("Error al reasignar memoria\n");
                exit(EXIT_FAILURE);
            }

            (*materias)[(*cantidadMaterias)++] = strdup(materia);
        }
    }
}

void generarInformacionMaterias(FILE *archivoEntrada, FILE *archivoSalida){
    // obtener la cantidad de aulas
    int cantidadAulas;
    fscanf(archivoEntrada, "%d", &cantidadAulas);
    fgetc(archivoEntrada);

    // verificar que no se repitan
    char **materias = NULL;
    int cantidadMaterias = 0;

    obtenerMaterias(&materias, &cantidadMaterias, archivoEntrada);

    // asignarles la informacion
    // imprimir en el archivo
    asignarInformacionMaterias(materias, cantidadAulas, cantidadMaterias, archivoSalida);


    // liberar memoria
    for(int i = 0; i<cantidadMaterias; i++){
        free(materias[i]);
    }

    free(materias);
}