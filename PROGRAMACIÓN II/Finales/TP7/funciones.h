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
    char *pais;
    char *genero;
    char *genero_de_preferencia;
    char *pais_de_preferencia;
} Persona;


FILE *obtenerArchivo(const char *nombre, const char *modo);

int esMatchValido(Persona *persona1, Persona *persona2);

void generarMatchs(Persona **personas, int cantidadPersonas, FILE *archivoMatchs);

Persona *generarPersona(char persona[]);

void liberarMemoriaPersona(Persona *persona);

void liberarMemoriaPersonas(Persona **personas, int cantidadPersonas);

void obtenerPersonas(Persona ***personas, int *cantidadPersonas, FILE *archivoPersonas, FILE *archivoUnmatched);

void obtenerDatosPersonas(FILE *archivoPersonas, FILE *archivoMatchs, FILE *archivoUnmatched);


#endif