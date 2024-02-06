#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// la cantidad MÁXIMA de filas y/o columnas del tablero es de 20 y una cantidad MÍNIMA de 10
// La cantidad MÁXIMA de barcos en el archivo es de 50
// Los barcos tienen longitudes entre 2 y 4 casillas, cualquier otra longitud es inválida

typedef struct {
    int fila; // En que fila se encuentra el extremo superior o izquierdo del barco
    int columna; // en que columna se encuentra dicho extremo
    int orientacion; // si es 0 indica que está posicionado horizontalmente si es 1 indica que es verticalmente
    int longitud; // longitud del barco (entre 2 y 4)
} Barco;

void obtenerBarcos(Barco barcos[], int *cantidadBarcos, FILE* archivoEntrada){
    char barco[100];

    while(*cantidadBarcos < 50 && fgets(barco, sizeof(barco), archivoEntrada) != NULL){
        Barco nuevoBarco;
        
        sscanf(barco, "%d %d %d %d", &nuevoBarco.fila, &nuevoBarco.columna, &nuevoBarco.orientacion, &nuevoBarco.longitud);
        if(nuevoBarco.longitud < 2 || nuevoBarco.longitud > 4){
            continue;
        } else {
            barcos[(*cantidadBarcos)] = nuevoBarco;
            (*cantidadBarcos)++;
        }
    }

    if(*cantidadBarcos >= 50){
        printf("Cantidad de barcos excedida %d\n", *cantidadBarcos);
        exit(EXIT_FAILURE);
    }
}

int esBarcoValido(Barco barco, int filas, int columnas, int casillasOcupadas[filas][columnas]){
    // verificar si cabe integramente dentro del tablero
    if((barco.fila < 1 || barco.fila >= filas) || (barco.columna < 1 || barco.columna >= columnas)){
        return 0;
    }

    // verificar si esta ubicado de forma horizontal o vertical (si tiene 0 o 1) 
    if(barco.orientacion != 0 && barco.orientacion != 1){
        return 0;
    }
    
    // verificar si el tamaño del barco es de 2, 3 o 4 casillas
    if(barco.longitud < 2 || barco.longitud > 4){
        return 0;
    }

    // Cada casilla del tablero puede contener una parte de un único barco
    if(casillasOcupadas[barco.fila][barco.columna]){
        return 0;
    }

    if(barco.orientacion == 0){  // Barco en posición horizontal
        for(int i = 0; i < barco.longitud; i++){
            if(casillasOcupadas[barco.fila][barco.columna + i]){
                return 0;
            }
        }
    } else {  // Barco en posición vertical
        for(int i = 0; i < barco.longitud; i++){
            if(casillasOcupadas[barco.fila + i][barco.columna]){
                return 0;
            }
        }
    }

    return 1;
}

void seleccionarBarcosAleatorios(Barco barcos[], int cantidadBarcos, int cantidadBarcosElegir, int filas, int columnas, int casillasOcupadas[filas][columnas], FILE* archivoSalida){
    srand(time(NULL));
    
    int barcosSeleccionados[cantidadBarcosElegir];

    for(int i = 0; i < cantidadBarcosElegir; i++){
        barcosSeleccionados[i] = 0;
    }

    for(int i = 0; i < cantidadBarcosElegir; i++){
        int barcoSeleccionado;

        do {
            barcoSeleccionado = rand() % cantidadBarcos;
        } while(barcosSeleccionados[barcoSeleccionado]);

        barcosSeleccionados[barcoSeleccionado] = 1;

        if(esBarcoValido(barcos[barcoSeleccionado], filas, columnas, casillasOcupadas)){
            // Marcar las casillas ocupadas en el array
            int fila = barcos[barcoSeleccionado].fila;
            int columna = barcos[barcoSeleccionado].columna;
            int orientacion = barcos[barcoSeleccionado].orientacion;
            int longitud = barcos[barcoSeleccionado].longitud;

            if (orientacion == 0) {  // Barco en posición horizontal
                for(int j = 0; j < longitud; j++){
                    casillasOcupadas[fila][columna + j] = 1;
                }
            } else {  // Barco en posición vertical
                for(int j = 0; j < longitud; j++){
                    casillasOcupadas[fila + j][columna] = 1;
                }
            }

            // Escribir el barco en el archivo de salida
            fprintf(archivoSalida, "%d %d %d %d\n", barcos[barcoSeleccionado].fila, barcos[barcoSeleccionado].columna, barcos[barcoSeleccionado].orientacion, barcos[barcoSeleccionado].longitud);
        }
    }
}

int main(){
    FILE *archivoEntrada;
    archivoEntrada = fopen("entrada.txt", "r");

    if(archivoEntrada == NULL){
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    int filas, columnas;
    int cantidadBarcos = 0;

    fscanf(archivoEntrada, "%d %d", &filas, &columnas);
    fgetc(archivoEntrada);

    if((filas < 10 || filas > 20) || (columnas < 10 || columnas > 20)){
        printf("Cantidad de filas o columnas inválidas\n");
        exit(EXIT_FAILURE);
    }

    FILE *archivoSalida;
    archivoSalida = fopen("salida.txt", "w");

    Barco barcos[50];
   
    obtenerBarcos(barcos, &cantidadBarcos, archivoEntrada);

    printf("cantidadBarcos: %d\n", cantidadBarcos);

    srand(time(NULL));

    int cantidadBarcosElegir = rand() % (columnas - (filas / 3) + 1) + (filas / 3);
    printf("cantidadBarcosElegir %d\n", cantidadBarcosElegir);

    int casillasOcupadas[filas][columnas];

    // rellenar array
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            casillasOcupadas[i][j] = 0;
        }
    }

    fprintf(archivoSalida, "%d %d\n", filas, columnas);

    seleccionarBarcosAleatorios(barcos, cantidadBarcos, cantidadBarcosElegir, filas, columnas, casillasOcupadas, archivoSalida);


    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", casillasOcupadas[i][j]);
        }
        printf("\n");
    }

    fclose(archivoEntrada);
    fclose(archivoSalida);

    return 0;
}