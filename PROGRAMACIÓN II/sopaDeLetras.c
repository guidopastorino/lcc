#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int numRandom(int min, int max){
    return rand() % (max - min + 1) + min;
}

void inicializarTablero(char ***tablero, int n){
    *tablero = (char**)malloc(sizeof(char*) * n);

    for(int i = 0; i<n; i++){
        (*tablero)[i] = (char*)malloc(sizeof(char) * n);
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            (*tablero)[i][j] = '_';
        }
    }
}

void imprimirTablero(char **tablero, int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }
}

void rellenarTablero(char **tablero, int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            if(!isalpha(tablero[i][j])){
                tablero[i][j] = (char)(numRandom(97, 122)); // ASCII 65 - 90 -> A-Z mayuscula || ASCII 97 - 122 -> a-z minúscula
            }
        }
    }
}

int tieneLugar(char **tablero, int n, char *palabra, int posicion, int fila, int columna){
    if(strlen(palabra) > n){
        printf("La longitud de la palabra %s es mayor que la del tablero (%d > %d)\n", palabra, strlen(palabra), n);
        return 0;
    }

    if(posicion != 0 && posicion != 1){
        printf("Número de posición inválido\n");
        return 0;
    }

    if(posicion == 0){
        if(columna + strlen(palabra) - 1 > n){
            return 0;
        }
        for(int i = 0; i<strlen(palabra); i++){
            if(tablero[fila - 1][columna - 1 + i] != '_' && tablero[fila - 1][columna - 1 + i] != palabra[i]){
                return 0;
            }
        }
    }

    if(posicion == 1){
        if(fila + strlen(palabra) - 1 > n){
            return 0;
        }
        for(int i = 0; i<strlen(palabra); i++){
            if(tablero[fila - 1 + i][columna - 1] != '_' && tablero[fila - 1 + i][columna - 1] != palabra[i]){
                return 0;
            }
        }
    }

    return 1;
}

void colocarPalabra(char **tablero, int n, char *palabra, int posicion, int fila, int columna){
    palabra = strlwr(palabra);

    if(tieneLugar(tablero, n, palabra, posicion, fila, columna)){
        for(int i = 0; i<strlen(palabra); i++){
            if(posicion == 0){
                tablero[fila - 1][columna - 1 + i] = palabra[i];
            }
            if(posicion == 1){
                tablero[fila - 1 + i][columna - 1] = palabra[i];
            }
        }
    } else {
        printf("No se ha podido colocar la palabra %s %s en la fila %d columna %d\n", palabra, posicion == 0 ? "horizontalmente" : "verticalmente", fila, columna);
    }
}


int main(){
    int n = 15;

    char **tablero = NULL;

    inicializarTablero(&tablero, n);

    char *palabras[] = {
        "gato", "perro", "elefante", "jirafa", "tigre",
        "leon", "mono", "cebra", "cocodrilo", "rinoceronte",
        "hipopotamo", "pinguino", "loro", "serpiente", "tortuga",
        "tucan", "ballena", "delfin", "koala", "canguro",
        "pulpo", "oso", "murcielago", "panda", "nutria",
        "avestruz", "leopardo", "medusa", "ciervo", "camello",
        "hipopotamo", "anguila", "gallina", "gavilan", "raton",
        "escarabajo", "ornitorrinco", "perezoso", "cangrejo", "abeja",
        "pavo", "avispa", "mosquito", "mosca", "hormiga",
        "cabra", "avestruz", "pato", "iguana", "tiburon"
    };

    int cantidadPalabras = sizeof(palabras) / sizeof(palabras[0]);
    int *palabrasSeleccionadas = (int*)malloc(sizeof(int) * cantidadPalabras);

    srand((unsigned int)time(NULL));

    for(int i = 0; i<cantidadPalabras; i++){
        int index;

        do {
            index = rand() % cantidadPalabras;
        } while(palabrasSeleccionadas[index] == 1);

        palabrasSeleccionadas[index] = 1;

        int posicion = rand() % 2;
        int fila = numRandom(1, n);
        int columna = numRandom(1, n);

        colocarPalabra(tablero, n, palabras[index], posicion, fila, columna);
    }


    rellenarTablero(tablero, n);

    imprimirTablero(tablero, n);


    free(palabrasSeleccionadas);

    for(int i = 0; i<n; i++){
        free(tablero[i]);
    }

    free(tablero);

    return 0;
}