#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    * Estructura que representa los horarios de una materia.
*/
typedef struct {
    char *dia;                  // Lunes, Martes, Miercoles, Jueves o Viernes
    // de las 8 a las 19, con diferencia maxima de 4 hs, los horarios no deben ser los mismos
    int horarioInicio;
    int horarioFinalizacion;
} Horarios;


/*
    * Estructura que representa una materia.
*/
typedef struct {
    char *nombre;               // Nombre de la materia
    int dias;                   // Dias de la materia (1, 2 o 3)
    Horarios *horarios;  // Horarios de la materia (dia de la semana, horario de inicio, horario de finalizacion)
} Materia;



/*
    * Obtiene un valor aleatorio entre el rango [min, max]
    * 
    * @param min: Limite inferior del range del numero aleatorio que queremos obtener
    * @param max: Limite superior del range del numero aleatorio que queremos obtener
    * @return Número aleatorio entre el rango [min, max]: 
    
*/
int numRandom(int min, int max);


/*
    * Verifica si el elemento pertenece al array o no
    * 
    * @param arr: Array de elementos (recibe la direccion de memoria)
    * @param el: Elemento a verificar si pertenece al array
    * @param size: Cantidad de elementos en el array
    * @return 1 si el elemento está en el array, 0 si no está.
*/
int estaEnArray(char ***arr, char *el, int size);


/*
    * Abre un archivo dependiendo el modo de lectura que se le pase
    *
    * @param archivo Nombre del archivo a abrir
    * @param modo Modo de lectura del archivo
    * @return Puntero al archivo

*/
FILE* obtenerArchivo(const char *archivo, const char *modo);


/*
    * Escribe en el archivo de salida la cantidad de aulas con la información de cada materia
    * 
    * @param informacionMaterias: Array de punteros a punteros de estructuras Materia
    * @param cantidadMaterias: Cantidad de materias
    * @param cantidadAulas: Cantidad de aulas
    * @param archivoSalida: Archivo en el cual se escribirá la información
*/
void generarArchivoSalida(Materia **informacionMaterias, int cantidadMaterias, int cantidadAulas, FILE *archivoSalida);


/*
    * Libera la memoria del array de punteros a punteros de estructuras Materia
    * 
    * @param informacionMaterias: Array de punteros a punteros de estructuras Materia
    * @param cantidadMaterias: Cantidad de materias
*/
void liberarMateriasConInformacion(Materia **informacionMaterias, int cantidadMaterias);


/*
    * Crea un array de punteros a puntero de estructura Materia y escribe los datos de las materias en el archivo de salida
    * 
    * @param materias: Array donde se almacenarán las materias
    * @param cantidadAulas: Cantidad de aulas
    * @param cantidadMaterias: Cantidad de materias
    * @param archivoSalida: Archivo en el cual se escribirá la información
*/
void asignarInformacionMaterias(char **materias, int cantidadAulas, int cantidadMaterias, FILE* archivoSalida);


/*
    * Obtiene las materias desde el archivo de entrada y las almacena en un array, sin que se repitan
    * 
    * @param materias: Array donde se almacenarán las materias
    * @param cantidadMaterias: Puntero a entero para manejar la cantidad de materias que se van almacenando
    * @param archivoEntrada: Archivo en el cual se obtendrán las materias
*/
void obtenerMaterias(char ***materias, int *cantidadMaterias, FILE *archivoEntrada);


/*
    * Recibe los archivos de entrada y salida. Primero realiza los procedimientos para obtener las materias y asignarles la informacion, luego genera un archivo de salida con los datos de las materias
    * 
    * @param archivoEntrada archivo en el cual se obtienen la cantidad de aulas y las materias
    * @param archivoSalida archivo en el se escribe la informacion
*/
void generarInformacionMaterias(FILE *archivoEntrada, FILE *archivoSalida);

#endif