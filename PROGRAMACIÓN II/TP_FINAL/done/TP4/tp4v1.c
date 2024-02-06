#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct {
    char nombre[100];
    char apellido[100];
    int edad;
    char localidad[100];
} Persona;

typedef struct {
    Persona persona1;
    Persona persona2;
} Pareja;

bool cumplenReglas(Persona persona1, Persona persona2){
    // las personas debían estar habitando en la misma localidad;
    if(strcasecmp(persona1.localidad, persona2.localidad) != 0){
        return false;
    }

    // aquellos menores de 16 años sólo podían estar unidos con alguien también menor;
    if(persona1.edad < 16 && persona2.edad >= 16){
        return false;
    }

    // los menores de 12 años no eran alcanzados por las flechas de Cupido;
    if(persona1.edad < 12 || persona2.edad < 12){
        return false;
    }

    // se buscaba evitar que dos personas del mismo apellido estén unidas;
    if(strcasecmp(persona1.apellido, persona2.apellido) == 0){
        return false;
    }

    // cada persona está unida, a lo sumo, a otra.
    return true;
}

void ingresarPersonas(Persona personas[], int *cantidadPersonas){
    printf("Cuantas personas deseas ingresar?");
    scanf("%d", cantidadPersonas);
    printf("cantidadPersonas: %d\n", (*cantidadPersonas));

    for(int i = 0; i<(*cantidadPersonas); i++){
        printf("Datos persona %d: \n", i + 1);
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

void armarParejas(Persona personas[], Pareja parejas[], Persona personasSinPareja[], int cantidadPersonas, int *cantidadParejas, int *cantidadPersonasSinPareja){
    FILE *archivo;
    archivo = fopen("salida.txt", "w");

    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    bool emparejado[cantidadPersonas];
    memset(emparejado, false, sizeof(emparejado));

    printf("Armando parejas...\n");

    fprintf(archivo, "Parejas: \n");

    for(int i = 0; i < cantidadPersonas; i++){
        if(!emparejado[i]){
            int candidato = -1;
            for(int intentos = 0; intentos < 10 && candidato == -1; intentos++){
                candidato = rand() % cantidadPersonas;
                if (!emparejado[candidato] && candidato != i && cumplenReglas(personas[i], personas[candidato])){
                    // imprimir parejas en el archivo
                    fprintf(archivo, "%s %s - %s %s\n", personas[i].nombre, personas[i].apellido, personas[candidato].nombre, personas[candidato].apellido);

                    // almacenar parejas
                    parejas[(*cantidadParejas)].persona1 = personas[i];
                    parejas[(*cantidadParejas)].persona2 = personas[candidato];

                    emparejado[i] = true;
                    emparejado[candidato] = true;


                    (*cantidadParejas)++;
                } else {
                    candidato = -1;  // Reiniciar el candidato si no se encuentra una pareja adecuada en este intento1
                }
            }
        }
    }

    // Identificar las personas sin pareja y almacenarlas en el array
    for(int i = 0; i<cantidadPersonas; i++){
        if(!emparejado[i]){
            personasSinPareja[(*cantidadPersonasSinPareja)] = personas[i];
            (*cantidadPersonasSinPareja)++;
        }
    }

    printf("Parejas formadas.\n");
    printf("cantidadParejas: %d\n", *cantidadParejas);

    fclose(archivo);
}

void imprimirNombreYApellidoDeParejasFormadas(Pareja parejas[], int cantidadParejas){
    if(cantidadParejas == 0){
        printf("No hay parejas formadas todavía\n");
        return;
    }

    for(int i = 0; i<cantidadParejas; i++){
        printf("Pareja %d: \n", i + 1);
        printf("%s %s - %s %s\n", parejas[i].persona1.nombre, parejas[i].persona1.apellido, parejas[i].persona2.nombre, parejas[i].persona2.apellido);
    }
}

void imprimirNombreYApellidoDePersonasSinPareja(Persona personasSinPareja[], int cantidadPersonasSinPareja){
    if(cantidadPersonasSinPareja == 0){
        printf("No hay parejas formadas todavía\n");
        return;
    }

    for(int i = 0; i<cantidadPersonasSinPareja; i++){
        printf("%s %s\n", personasSinPareja[i].nombre, personasSinPareja[i].apellido);
    }
}


int main(){
    Persona personas[500];
    int cantidadPersonas;

    Pareja parejas[500];
    int cantidadParejas = 0;

    Persona personasSinPareja[500];
    int cantidadPersonasSinPareja = 0;

    int opcion;
    

    do{
        printf("0. Salir del programa.\n");
        printf("1. Permitir el ingreso de los datos de las personas.\n");
        printf("2. armar parejas teniendo en cuenta que para cada persona se elige su pareja al azar, entre todos los posibles candidatos (aquellos que cumplen con las reglas anteriores).\n");
        printf("3. Imprimir nombre y apellido de los integrantes de cada pareja formada.\n");
        printf("4. Imprimir nombre y apellido de aquellas personas que quedaron solas (por no poder encontrar candidato o porque no cumplió alguna regla).\n");

        printf("Elija una opción: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 0:
                break;
            case 1:
                ingresarPersonas(personas, &cantidadPersonas);
                break;
            case 2:
                armarParejas(personas, parejas, personasSinPareja, cantidadPersonas, &cantidadParejas, &cantidadPersonasSinPareja);
                break;
            case 3:
                imprimirNombreYApellidoDeParejasFormadas(parejas, cantidadParejas);
                break;
            case 4:
                imprimirNombreYApellidoDePersonasSinPareja(personasSinPareja, cantidadPersonasSinPareja);
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.");
        }
    }while(opcion != 0);


    return 0;
}
