#include "funciones.h"

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Uso: %s <archivo_salida_cifrado_caracteres> <archivo_salida_mensaje_cifrado>", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *archivoCifradoCaracteres = abrirArchivo(argv[1], "w");
    FILE *archivoCifradoMensaje = abrirArchivo(argv[2], "w");

    srand((unsigned int)time(NULL));

    generarCifrado(archivoCifradoCaracteres, archivoCifradoMensaje);

    fclose(archivoCifradoCaracteres);
    fclose(archivoCifradoMensaje);

    return 0;
}