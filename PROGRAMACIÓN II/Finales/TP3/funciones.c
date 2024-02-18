#include "funciones.h"

FILE *obtenerArchivo(const char *archivo, const char *modo){
    FILE *fp = fopen(archivo, modo);

    if(fp == NULL){
        printf("No se puedo abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    return fp;
}

int esBarcoValido(Barco *barco, int filas, int columnas, int casillasOcupadas[filas][columnas]){
    // Un barcos sólo puede ubicarse de forma horizontal o vertical (o sea, validar que el 3er valor asociado a un barco es 0 o 1)
    if(barco->posicion != 0 && barco->posicion != 1){
        return 0;
    }

    // Cada barco debe caber íntegramente dentro del tablero
    if((barco->posicion == 0 && (barco->longitud > filas)) || (barco->posicion == 1 && (barco->longitud > columnas)) || (barco->fila < 1) || (barco->columna < 1)){
        return 0;
    }


    // El tamaño de cada barco es de 2, 3 o 4 casillas
    if(barco->longitud < 2 || barco->longitud > 4){
        return 0;
    }


    // Cada casilla del tablero puede contener una parte de un único barco
    if(casillasOcupadas[barco->fila - 1][barco->columna - 1] == 1){
        return 0;
    }

    if(barco->posicion == 0){
        for(int i = 0; i<barco->longitud; i++){
            if(casillasOcupadas[barco->fila - 1][barco->columna - 1 + i] == 1){
                return 0;
            }
        }
    } else {
        for(int i = 0; i<barco->longitud; i++){
            if(casillasOcupadas[barco->fila - 1 + i][barco->columna - 1] == 1){
                return 0;
            }
        }
    }

    return 1;
}

void seleccionarBarcos(Barco **barcos, int cantidadBarcos, int cantidadBarcosElegir, int filas, int columnas, FILE *archivoSalida){
    fprintf(archivoSalida, "%d %d\n", filas, columnas);

    int casillasOcupadas[filas][columnas];

    for(int i = 0; i<filas; i++){
        for(int j = 0; j<columnas; j++){
            casillasOcupadas[i][j] = 0;
        }
    }

    int barcosSeleccionados[cantidadBarcos];

    for(int i = 0; i<cantidadBarcos; i++){
        barcosSeleccionados[i] = 0;
    }

    for(int i = 0; i<cantidadBarcosElegir; i++){
        int barcoSeleccionado;

        do {
            barcoSeleccionado = rand() % cantidadBarcos;
        } while(barcosSeleccionados[barcoSeleccionado] || !esBarcoValido(barcos[barcoSeleccionado], filas, columnas, casillasOcupadas));

        barcosSeleccionados[barcoSeleccionado] = 1;

        // rellenar tablero con el lugar que ocupa el barco
        for(int j = 0; j<barcos[barcoSeleccionado]->longitud; j++){
            if(barcos[barcoSeleccionado]->posicion == 0){
                casillasOcupadas[barcos[barcoSeleccionado]->fila - 1][barcos[barcoSeleccionado]->columna - 1 + j] = 1;
            } else {
                casillasOcupadas[barcos[barcoSeleccionado]->fila - 1 + j][barcos[barcoSeleccionado]->columna - 1] = 1;
            }
        }

        // imprimir barco en el archivo de salida
        fprintf(archivoSalida, "%d %d %d %d\n", barcos[barcoSeleccionado]->fila, barcos[barcoSeleccionado]->columna, barcos[barcoSeleccionado]->posicion, barcos[barcoSeleccionado]->longitud);
    }
}

void obtenerBarcos(Barco ***barcos, int *cantidadBarcos, FILE *archivoEntrada){
    char barco[50];

    while(*cantidadBarcos <= 50 && fgets(barco, sizeof(barco), archivoEntrada) != NULL){
        Barco *nuevoBarco = (Barco*)malloc(sizeof(Barco));

        sscanf(barco, "%d %d %d %d\n", &nuevoBarco->fila, &nuevoBarco->columna, &nuevoBarco->posicion, &nuevoBarco->longitud);
        
        if(nuevoBarco->longitud < 2 || nuevoBarco->longitud > 4){
            free(nuevoBarco);
        } else {
            (*cantidadBarcos)++;
            *barcos = realloc(*barcos, sizeof(Barco*) * (*cantidadBarcos));
            (*barcos)[(*cantidadBarcos) - 1] = nuevoBarco;
        }
    }

    if(*cantidadBarcos > 50){
        printf("La cantidad máxima de barcos debe ser de 50.\n");
        exit(EXIT_FAILURE);
    }
}

void generarTablero(FILE *archivoEntrada, FILE *archivoSalida){
    int filas, columnas;

    fscanf(archivoEntrada, "%d %d", &filas, &columnas);

    fgetc(archivoEntrada);

    if((filas < 1 || filas > 20) || (columnas < 1 || columnas > 20)){
        printf("Número de filas o columnas no válido\n");
        exit(EXIT_FAILURE);
    }

    Barco **barcos = NULL;
    int cantidadBarcos = 0;

    obtenerBarcos(&barcos, &cantidadBarcos, archivoEntrada);

    int cantidadBarcosElegir = rand() % (columnas - (filas / 3) + 1) + (filas / 3);
    
    seleccionarBarcos(barcos, cantidadBarcos, cantidadBarcosElegir, filas, columnas, archivoSalida);


    // liberar memoria
    for(int i = 0; i<cantidadBarcos; i++){
        free(barcos[i]);
    }

    free(barcos);
}