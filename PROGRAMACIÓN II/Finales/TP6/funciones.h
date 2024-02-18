#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*
 * Genera un número aleatorio en el rango [min, max].
 *
 * @param min: Valor mínimo del rango.
 * @param max: Valor máximo del rango.
 * @return Número aleatorio generado.
 */
int randomNum(int min, int max);

/*
 * Abre un archivo en el modo especificado y maneja errores en caso de falla.
 *
 * @param archivo: Nombre del archivo a abrir.
 * @param modo: Modo en el que se abrirá el archivo (lectura, escritura, etc.).
 * @return Puntero al archivo abierto.
 */
FILE *abrirArchivo(const char *archivo, const char *modo);

/*
 * Selecciona palabras del archivo de diccionario que tienen una longitud menor o igual a n.
 *
 * @param archivoDiccionario: Puntero al archivo de diccionario.
 * @param n: Longitud máxima permitida para las palabras seleccionadas.
 * @param palabras: Puntero a un puntero de cadenas donde se almacenarán las palabras seleccionadas.
 * @param cantidadPalabras: Puntero a la variable que almacenará la cantidad de palabras seleccionadas.
 */
void seleccionarPalabras(FILE *archivoDiccionario, int n, char ***palabras, int *cantidadPalabras);

/*
 * Selecciona palabras y las coloca en el archivo de salida, alternando entre VERTICAL y HORIZONTAL.
 *
 * @param palabras: Puntero a un arreglo de cadenas que contiene las palabras seleccionadas.
 * @param cantidadPalabras: Cantidad total de palabras seleccionadas.
 * @param archivoSalida: Puntero al archivo de salida donde se colocarán las palabras.
 */
void seleccionarPalabrasConPosicion(char **palabras, int cantidadPalabras, FILE *archivoSalida);

/*
 * Gestiona la información del tablero, seleccionando palabras y generando la disposición en el archivo de salida.
 *
 * @param archivoDiccionario: Puntero al archivo de diccionario.
 * @param archivoSalida: Puntero al archivo de salida donde se colocará la información del tablero.
 */
void gestionarInformacionTablero(FILE *archivoDiccionario, FILE *archivoSalida);

#endif