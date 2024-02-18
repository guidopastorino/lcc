#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
    * Crea un nuevo puntero al archivo indicado dependiendo del modo de lectura que se le pase
    *
    * @param nombre Nombre del archivo a abrir
    * @param modo Modo de lectura del archivo
    * @return Puntero a un archivo
*/
FILE *obtenerArchivo(const char *nombre, const char *modo);


/*
    * Construye n cantidades de afinidades. Luego las imprime en el archivo de salida
    *
    * @param personas Array de punteros a puntero de caracteres en el cual contiene a las personas que formarán las afinidades
    * @param cantidadPersonas Cantidad de personas que fueron obtenidas y almacenadas en el array **personas
    * @param afinidades_a_construir Cantidad de afinidades que se van a construir
    * @param archivoSalida Archivo en el cual las afinidades se imprimen
*/
void construirAfinidades(char **personas, int cantidadPersonas, int afinidades_a_construir, FILE *archivoSalida);


/*
    * Imprime las personas almacenadas en el array **personas en el archivo de salida
    *
    * @param personas Array de punteros a puntero de caracteres
    * @param cantidadPersonas Cantidad de personas que fueron obtenidas y almacenadas en el array **personas
    * @param archivoSalida Archivo en el cual se imprimen las personas
*/
void imprimirPersonasSalida(char **personas, int cantidadPersonas, FILE *archivoSalida);


/*
    * Libera la memoria dinámica ocupada por las personas mientras se obtenian desde el archivo de entrada
    *
    * @param personas Array de punteros a puntero de caracteres que contiene las personas
    * @param cantidadPersonas Cantidad de personas que fueron obtenidas
*/
void liberarMemoriaPersonas(char **personas, int cantidadPersonas);


/*
    * Obtiene las personas desde el archivo de entrada para almacenarlas en el array **personas. Mientras se obtienen, se incrementa la cantidad de personas y se modifica el tamaño del array **personas.
    *
    * @param personas Array de punteros a puntero de caracteres que almacenará a las personas
    * @param cantidadPersonas Puntero a entero para poder dereferenciarlo y modificar su valor (incrementarlo)
    * @param archivoEntrada Archivo en el cual se obtendrán las personas
*/
void obtenerPersonas(char ***personas, int *cantidadPersonas, FILE *archivoEntrada);


/*
    * A partir de dos archivos, esta funcion se encarga de generar las afinidades, obteniedo las personas, almacenandolas en el array y contruyendo las afinidades una por una.
    *
    * @param archivoEntrada Archivo en el cual se obtendrán las personas
    * @param archivoSalida Archivo en el cual se imprimirán las afinidades
*/
void generarAfinidades(FILE *archivoEntrada, FILE* archivoSalida);

#endif