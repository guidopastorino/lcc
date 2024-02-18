#include "funciones.h"

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Uso: %s <archivo_datos_personas> <archivo_parejas> <archivo_personas_sin_pareja>\n", argv[0]);
    }

    generarArchivosMenu(argv[1], argv[2], argv[3]);

    return 0;
}