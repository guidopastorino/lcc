#include "funciones.h"

FILE *abrirArchivo(const char *archivo, const char *modo){
    FILE *fp = fopen(archivo, modo);

    if(fp == NULL){
        printf("Error al abrir el archivo '%s'\n", archivo);
        exit(EXIT_FAILURE);
    }

    return fp;
}

void generarClaves(FILE *archivoCifradoCaracteres, LetraCifrado ***letrasCifradas){
    char *claves = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    *letrasCifradas = (LetraCifrado**)malloc(sizeof(LetraCifrado*) * strlen(claves));

    int *letrasYaUsadas = (int*)malloc(sizeof(int) * strlen(claves));
    memset(letrasYaUsadas, 0, sizeof(int) * strlen(claves));

    for(int i = 0; i<strlen(claves); i++){
        int indexLetra;

        do {
            indexLetra = rand() % strlen(claves);
        } while (letrasYaUsadas[indexLetra] == 1 || claves[indexLetra] == claves[i]);
        
        letrasYaUsadas[indexLetra] = 1;

        (*letrasCifradas)[i] = (LetraCifrado*)malloc(sizeof(LetraCifrado));
        (*letrasCifradas)[i]->letra = claves[i];
        (*letrasCifradas)[i]->cifrado = claves[indexLetra];

        fprintf(archivoCifradoCaracteres, "%c -> %c\n", (*letrasCifradas)[i]->letra, (*letrasCifradas)[i]->cifrado);
    }
    
    
    free(letrasYaUsadas);
}

void cifrarMensaje(LetraCifrado **letrasCifradas, FILE *archivoCifradoMensaje){
    char mensaje[100];

    printf("Mensaje a cifrar: ");
    scanf("%99[^\n]", mensaje);

    for(int i = 0; mensaje[i] != '\0'; i++){
        if(isalpha(mensaje[i])){
            for(int j = 0; j<26; j++){
                if(tolower(mensaje[i]) == tolower(letrasCifradas[j]->letra)){
                    mensaje[i] = letrasCifradas[j]->cifrado;
                    break;
                }
            }
        } else {
            mensaje[i] = toupper(mensaje[i]);
        }
        
    }

    printf("Mensaje cifrado: %s", mensaje);
    
    fprintf(archivoCifradoMensaje, "%s", mensaje);
}

void generarCifrado(FILE *archivoCifradoCaracteres, FILE *archivoCifradoMensaje){
    LetraCifrado **letrasCifradas = NULL;

    generarClaves(archivoCifradoCaracteres, &letrasCifradas);

    cifrarMensaje(letrasCifradas, archivoCifradoMensaje);

    for(int i = 0; i<26; i++){
        free(letrasCifradas[i]);
    }

    free(letrasCifradas);
}