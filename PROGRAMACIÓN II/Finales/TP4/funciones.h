#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    char *nombre;
    char *apellido;
    int edad;
    char *localidad;
} Persona;

typedef struct {
    Persona *persona1;
    Persona *persona2;
} Pareja;



/*

*/
FILE *abrirArchivo(const char *nombre, const char *modo);

/*

*/
void ingresarDatosPersonas(Persona ***personas, int *cantidadPersonas, const char *archivoDatosPersona);

/*

*/
void imprimirParejasFormadas(Pareja **parejas, int cantidadParejas, const char *archivoParejas);

/*

*/
void imprimirPersonasSinPareja(Persona **personasSinParejas, int cantidadPersonasSinParejas, const char *archivoPersonasSinParejas);

/*

*/
int esParejaValida(Persona *persona1, Persona *persona2);


/*

*/
void armarParejas(Persona **personas, int cantidadPersonas, Pareja ***parejas, int *cantidadParejas, Persona ***personasSinParejas, int *cantidadPersonasSinParejas);

/*

*/
void generarArchivosMenu(const char *archivoDatosPersona, const char *archivoParejas, const char *archivoPersonasSinParejas);



#endif