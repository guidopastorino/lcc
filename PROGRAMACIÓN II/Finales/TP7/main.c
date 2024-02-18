#include "funciones.h"

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Uso: %s <archivo_datos_personas> <archivo_parejas> <archivo_sin_parejas>", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *archivoPersonas = obtenerArchivo(argv[1], "r");
    FILE *archivoMatchs = obtenerArchivo(argv[2], "w");
    FILE *archivoUnmatched = obtenerArchivo(argv[3], "w");

    obtenerDatosPersonas(archivoPersonas, archivoMatchs, archivoUnmatched);

    fclose(archivoPersonas);
    fclose(archivoMatchs);
    fclose(archivoUnmatched);

    return 0;
}