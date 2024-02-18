#include "funciones.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Uso: %s <archivo_diccionario> <archivo_salida> \n", argv[0]);
        exit(1);
    }

    FILE *archivoDiccionario = abrirArchivo(argv[1], "r");
    FILE *archivoSalida = abrirArchivo(argv[2], "w");

    srand((unsigned int)time(NULL));

    gestionarInformacionTablero(archivoDiccionario, archivoSalida);

    fclose(archivoDiccionario);
    fclose(archivoSalida);

    return 0;
}