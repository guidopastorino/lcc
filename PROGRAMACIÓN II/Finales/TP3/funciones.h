#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    int fila;
    int columna;
    int posicion;
    int longitud;
} Barco;

/*
    * Abre un archivo especificado en el modo especificado. Si no se puede abrir el archivo, se sale del programa con un mensaje de error.
    * 
    * @param archivo Puntero a una cadena de caracteres que representa el nombre del archivo
    * @param modo Puntero a una cadena de caracteres que representa el modo de lectura del archivo
    * @return Puntero al archivo abierto
*/
FILE *obtenerArchivo(const char *archivo, const char *modo);



/*
    * Permite identificar si un barco es válido o no para colocarse en el tablero
    * 
    * @param barco Puntero a una estructura Barco, la cual contiene la informacion del barco a verificar
    * @param filas Cantidad de filas del tablero
    * @param columnas Cantidad de columnas del tablero
    * @param casillasOcupadas Array bidimensional que almacena las casillas ocupadas del tablero (si la caasilla es 1, entonces está ocupada)
    * @return 1 si el barco es válido a colocarse en el tablero, 0 si no es válido
*/
int esBarcoValido(Barco *barco, int filas, int columnas, int casillasOcupadas[filas][columnas]);



/*
    * Selecciona aleatoriamente barcos que fueron obtenidos desde el archivo de entrada, verificando si son barcos válidos para ser colocados en el tablero y luego los imprime en el archivo de salida
    * 
    * @param barcos Puntero a punteros de estructuras de Barco. Almacena la informacion de los barcos obtenidos
    * @param cantidadBarcos Cantidad de barcos almacenados en **barcos
    * @param cantidadBarcosElegir Cantidad aleatorio de barcos que van a ser seleccionados desde **barcos
    * @param filas Cantidad de filas del tablero
    * @param columnas Cantidad de columnas del tablero
    * @param archivoSalida Archivo en el cual se imrpimirá la información de los barcos que han sido seleccionados
*/
void seleccionarBarcos(Barco **barcos, int cantidadBarcos, int cantidadBarcosElegir, int filas, int columnas, FILE *archivoSalida);



/*
    * Desde un archivo de entrada, obtiene la informacion de todos los barcos (si es que los mismos son válidos) y los almacena en un array que se le pasa como puntero. Si la cantidad de barcos es mayor que 50, detiene el programa 
    * 
    * @param barcos Puntero a puntero de punteros de estructuras Barco, las cuales almacenarán la información de los barcos que se obtienen
    * @param cantidadBarcos Puntero a entero, el cual se incrementará si se obtuvo un nuevo barco
    * @param archivoEntrada Archivo del cual se obtiene la información
*/
void obtenerBarcos(Barco ***barcos, int *cantidadBarcos, FILE *archivoEntrada);



/*
    * Genera la informacion de los barcos a partir del archivo de entrada, tambien escanes las filas y columnas y, si las mismas son de dimensiones no válidas, se sale del programa
    * 
    * @param archivoEntrada Archivo del cual se obtiene la información
    * @param archivoSalida Archivo en el cual se imrpimirá la información (filas, columnas y barcos seleccionados)
*/
void generarTablero(FILE *archivoEntrada, FILE *archivoSalida);


#endif