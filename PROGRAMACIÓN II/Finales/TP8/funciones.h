#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

/*
 * Estructura que representa un par (basandose en clave y valor) para el cifrado de caracteres.
 * @param letra caracter del alfabeto
 * @param cifrado caracter del alfabeto cifrado
 */
typedef struct
{
    char letra;
    char cifrado;
} LetraCifrado;

/*
 * Se encarga de abrir un archivo en el modo especificado.
 * Imprime un mensaje de error y termina el programa si no puede abrir el archivo.
 * @param archivo: Una cadena que representa el nombre del archivo que se va a abrir.
 * @param modo: Una cadena que especifica el modo en que se abrirá el archivo (lectura, escritura, etc.).
 * @return Devuelve un puntero al archivo abierto.
 */
FILE *abrirArchivo(const char *archivo, const char *modo);

/*
 * Genera claves de cifrado, asignando a cada letra del alfabeto una letra cifrada de manera aleatoria.
 * Imprime las claves en un archivo dado.
 * @param archivoCifradoCaracteres: Puntero al archivo donde se imprimirán las claves generadas.
 * @param letrasCifradas: Puntero a un puntero que se utilizará para almacenar las letras cifradas generadas.
 */
void generarClaves(FILE *archivoCifradoCaracteres, LetraCifrado ***letrasCifradas);

/*
 * Cifra un mensaje ingresado por el usuario utilizando las claves generadas previamente.
 * El mensaje cifrado se imprime en la consola y se guarda en un archivo.
 * @param letrasCifradas: Puntero a un array de estructuras LetraCifrado que contiene las claves de cifrado.
 * @param archivoCifradoMensaje: Puntero al archivo donde se imprimirá el mensaje cifrado.
 */
void cifrarMensaje(LetraCifrado **letrasCifradas, FILE *archivoCifradoMensaje);

/*
 * Coordina la generación de claves y el cifrado de un mensaje, utilizando las funciones anteriores.
 * Libera la memoria asignada para las letras cifradas.
 * @param archivoCifradoCaracteres: Puntero al archivo donde se imprimirán las claves generadas.
 * @param archivoCifradoMensaje: Puntero al archivo donde se imprimirá el mensaje cifrado.
 */
void generarCifrado(FILE *archivoCifradoCaracteres, FILE *archivoCifradoMensaje);

#endif
