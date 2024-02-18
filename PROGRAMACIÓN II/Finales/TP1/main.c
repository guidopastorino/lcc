#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Uso: %s <archivo_entrada> <archivo_salida>", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *archivoEntrada = obtenerArchivo(argv[1], "r");
    FILE *archivoSalida = obtenerArchivo(argv[2], "w");
    
    srand(time(NULL));

    generarInformacionMaterias(archivoEntrada, archivoSalida);

    fclose(archivoEntrada);
    fclose(archivoSalida);

    return 0;
}