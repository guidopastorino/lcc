#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void imprimirPalabra(char *letrasAdivinadas){
    for(int i = 0; i<strlen(letrasAdivinadas); i++){
        printf("%c ", letrasAdivinadas[i]);
    }
    printf("\n");
}

void realizarJugada(char *palabraSecreta, char *letrasAdivinadas, char letra, int *vidas){
    int ascierto = 0;
    for(int i = 0; i<strlen(letrasAdivinadas); i++){
        if(letra == palabraSecreta[i]){
            letrasAdivinadas[i] = letra;
            ascierto = 1;
        }
    }

    if(!ascierto){
        printf("La letra %c no existe en la palabra. Intenta de nuevo con otra.\n", letra);
        (*vidas)--;
        return;
    }
}

int verificarJugada(char *palabraSecreta, char *letrasAdivinadas, int vidas){
    if(strcasecmp(palabraSecreta, letrasAdivinadas) == 0 && vidas > 0){
        imprimirPalabra(letrasAdivinadas);
        printf("Felicitaciones! Has adivinado la palabra!\n");
        return 1;
    } else if(vidas <= 0){
        printf("Se te han acabado las vidas, la palabra era: %s\n", palabraSecreta);
        return 0;
    }

    return -1;
}

int main(){
    char *palabras[] = {"PROGRAMACION", "COMPUTACION", "FIREBASE"};
    int cantidadPalabras = sizeof(palabras) / sizeof(palabras[0]);
    char *palabraSecreta;
    srand(time(NULL));
    palabraSecreta = palabras[rand() % cantidadPalabras];
    char letrasAdivinadas[50];
    memset(letrasAdivinadas, '_', strlen(palabraSecreta));
    letrasAdivinadas[strlen(palabraSecreta)] = '\0';

    int vidas = 6;

    char letra;

    while(1){
        printf("Vidas: %d\n", vidas);
        imprimirPalabra(letrasAdivinadas);
        printf("Escribe una letra: ");
        scanf(" %c", &letra);
        letra = toupper(letra);

        if(strchr(letrasAdivinadas, letra) != NULL){
            printf("Ya has ingresado la letra %c. Intenta con otra.\n");
            continue;
        }

        realizarJugada(palabraSecreta, letrasAdivinadas, letra, &vidas);

        int resultado = verificarJugada(palabraSecreta, letrasAdivinadas, vidas);

        if(resultado != -1){
            break;
        }
    }


    return 0;
}