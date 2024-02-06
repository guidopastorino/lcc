#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    char nombre[100];
    char apellido[100];
    int edad;
    char localidad[100];
} Persona;

void ingresarPersonas(Persona personas[], int n){
    for(int i = 0; i<n; i++){
        printf("Datos persona %d:\n", i+1);
        printf("Nombre: ");
        scanf("%s", personas[i].nombre);
        printf("Apellido: ");
        scanf("%s", personas[i].apellido);
        printf("Edad: ");
        scanf("%d", &personas[i].edad);
        printf("Localidad: ");
        scanf("%s", personas[i].localidad);
    }
}

void imprimirPersonas(Persona personas[], int n, FILE *archivoSalida){
    for(int i = 0; i<n; i++){
        fprintf(archivoSalida, "%s, %s, %d, %s\n", personas[i].nombre, personas[i].apellido, personas[i].edad, personas[i].localidad);
    }
}

int main(){
    int n;
    printf("Cuantas personas deseas ingresar? ");
    scanf("%d", &n);

    Persona personas[n];

    ingresarPersonas(personas, n);

    FILE *archivoSalida;
    archivoSalida = fopen("salida.txt", "w");

    if(archivoSalida == NULL){
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    imprimirPersonas(personas, n, archivoSalida);

    return 0;
}