#include "funciones.h"

FILE *abrirArchivo(const char *nombre, const char *modo){
    FILE *fp = fopen(nombre, modo);

    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    return fp;
}

void ingresarDatosPersonas(Persona ***personas, int *cantidadPersonas, const char *archivoDatosPersona){
    // Imprimirlos en un archivo los datos de las personas y almacenarlos en un array para poder usarlos para formar parejas.

    FILE *file = abrirArchivo(archivoDatosPersona, "w");

    printf("Cuantas personas deseas ingresar? ");
    scanf("%d", cantidadPersonas);
    printf("cantidadPersonas %d\n", *cantidadPersonas);

    *personas = (Persona**)malloc(sizeof(Persona**) * (*cantidadPersonas));

    for(int i = 0; i<(*cantidadPersonas); i++){
        (*personas)[i] = (Persona*)malloc(sizeof(Persona*));

        char buffer[256]; // variable temporal para poder almacenar su contenido

        printf("Datos persona %d: \n", i+1);

        printf("Nombre: ");
        scanf("%s", buffer);
        (*personas)[i]->nombre = strdup(buffer);
                
        printf("Apellido: ");
        scanf("%s", buffer);
        (*personas)[i]->apellido = strdup(buffer);
                
        printf("Edad: ");
        scanf("%d", &(*personas)[i]->edad);
                
        printf("Localidad: ");
        scanf(" %99[^\n]", buffer);
        (*personas)[i]->localidad = strdup(buffer);
    }

    // imprimir personas
    for(int i = 0; i<(*cantidadPersonas); i++){
        fprintf(file, "%s, %s, %d, %s\n", (*personas)[i]->nombre, (*personas)[i]->apellido, (*personas)[i]->edad, (*personas)[i]->localidad);
    }


    fclose(file);
}

void imprimirParejasFormadas(Pareja **parejas, int cantidadParejas, const char *archivoParejas){
    if(cantidadParejas < 1){
        printf("Todavía no hay parejas formadas.\n");
        return;
    }

    FILE *file = abrirArchivo(archivoParejas, "w");

    for(int i = 0; i<cantidadParejas; i++){
        fprintf(file, "%s %s %d %s - %s %s %d %s\n", parejas[i]->persona1->nombre, parejas[i]->persona1->apellido, parejas[i]->persona1->edad, parejas[i]->persona1->localidad, parejas[i]->persona2->nombre, parejas[i]->persona2->apellido, parejas[i]->persona2->edad, parejas[i]->persona2->localidad);
    }

    printf("Parejas generadas en el archivo: \'%s\'\n", archivoParejas);

    fclose(file);
}

void imprimirPersonasSinPareja(Persona **personasSinParejas, int cantidadPersonasSinParejas, const char *archivoPersonasSinParejas){
    if(cantidadPersonasSinParejas < 1){
        printf("No hay personas sin parejas.\n");
        return;
    }

    FILE *file = abrirArchivo(archivoPersonasSinParejas, "w");

    for(int i = 0; i<cantidadPersonasSinParejas; i++){
        fprintf(file, "%s %s %d %s\n", personasSinParejas[i]->nombre, personasSinParejas[i]->apellido, personasSinParejas[i]->edad, personasSinParejas[i]->localidad);
    }

    printf("Personas sin parejas generadas en el archivo: \'%s\'\n", archivoPersonasSinParejas);

    fclose(file);
}

int esParejaValida(Persona *persona1, Persona *persona2){
    // las personas debían estar habitando en la misma localidad;
    if(strcasecmp(persona1->localidad, persona2->localidad) != 0){
        return 0;
    }

    // aquellos menores de 16 años sólo podían estar unidos con alguien también menor;
    if(persona1->edad < 16 && persona2->edad >= 16){
        return 0;
    }

    // los menores de 12 años no eran alcanzados por las flechas de Cupido;
    if(persona1->edad < 12 || persona2->edad < 12){
        return 0;
    }

    // se buscaba evitar que dos personas del mismo apellido estén unidas
    if(strcasecmp(persona1->apellido, persona2->apellido) == 0){
        return 0;
    }

    return 1;
}

void armarParejas(Persona **personas, int cantidadPersonas, Pareja ***parejas, int *cantidadParejas, Persona ***personasSinParejas, int *cantidadPersonasSinParejas){
    // Las relaciones de las personas deben ser 1 a 1 (no se deben repetir las parejas ni tampoco una persona puede tener relaciones con mas de 1 persona)

    int *matched = (int*)malloc(sizeof(int) * cantidadPersonas);
    memset(matched, 0, sizeof(int) * cantidadPersonas);
    printf("sizeof matched %lu\n", sizeof(int) * cantidadPersonas);

    for(int i = 0; i<cantidadPersonas; i++){
        if(!matched[i]){
            int candidato = -1;
            for(int intentos = 10; intentos > 0 && candidato == -1; intentos--){
                candidato = rand() % cantidadPersonas;
                if(!matched[candidato] && i != candidato && esParejaValida(personas[i], personas[candidato])){
                    (*cantidadParejas)++;
                    *parejas = (Pareja**)realloc(*parejas, sizeof(Pareja**) * (*cantidadParejas));
                    (*parejas)[(*cantidadParejas) - 1] = (Pareja*)malloc(sizeof(Pareja));
                    (*parejas)[(*cantidadParejas) - 1]->persona1 = personas[i];
                    (*parejas)[(*cantidadParejas) - 1]->persona2 = personas[candidato];

                    matched[i] = 1;
                    matched[candidato] = 1;
                } else {
                    candidato = -1;
                }
            }
        }
    }

    // detectar personas que no pudieron formar parejas:
    for(int i = 0; i<cantidadPersonas; i++){
        if(!matched[i]){
            (*cantidadPersonasSinParejas)++;
            *personasSinParejas = (Persona**)realloc(*personasSinParejas, sizeof(Persona**) * (*cantidadPersonasSinParejas));
            (*personasSinParejas)[(*cantidadPersonasSinParejas) - 1] = (Persona*)malloc(sizeof(Persona));
            (*personasSinParejas)[(*cantidadPersonasSinParejas) - 1] = personas[i];
        }
    }

    printf("cant personas: %d\n", cantidadPersonas);
    printf("cant parejas: %d\n", *cantidadParejas);
    printf("cant personas sin parejas: %d\n", *cantidadPersonasSinParejas);

    free(matched);
}

void liberarMemoria(Persona **personas, int cantidadPersonas, Pareja **parejas, int cantidadParejas, Persona **personasSinParejas, int cantidadPersonasSinParejas){
    // liberar memoria personas
    for(int i = 0; i<cantidadPersonas; i++){
        free(personas[i]->nombre);
        free(personas[i]->apellido);
        free(personas[i]->localidad);
        free(personas[i]);
    }
    free(personas);

    // liberar memoria parejas
    for(int i = 0; i<cantidadParejas; i++){
        free(parejas[i]->persona1->nombre);
        free(parejas[i]->persona1->apellido);
        free(parejas[i]->persona1->localidad);
        free(parejas[i]->persona2->nombre);
        free(parejas[i]->persona2->apellido);
        free(parejas[i]->persona2->localidad);
        free(parejas[i]);
    }
    free(parejas);

    // liberar memoria personas sin pareja
    for(int i = 0; i<cantidadPersonasSinParejas; i++){
        free(personasSinParejas[i]->nombre);
        free(personasSinParejas[i]->apellido);
        free(personasSinParejas[i]->localidad);
        free(personasSinParejas[i]);
    }
    free(personasSinParejas);
}

void generarArchivosMenu(const char *archivoDatosPersona, const char *archivoParejas, const char *archivoPersonasSinParejas){
    Persona **personas = NULL;
    int cantidadPersonas = 0;

    Pareja **parejas = NULL;
    int cantidadParejas = 0;

    Persona **personasSinParejas = NULL;
    int cantidadPersonasSinParejas = 0;

    int opcion;

    do {
        printf("--- Menú de opciones ---\n");
        printf("0. Salir del programa (terminar ejecución).\n");
        printf("1. Permitir el ingreso de los datos de las personas.\n");
        printf("2. Armar parejas.\n");
        printf("3. Imprimir nombre y apellido de los integrantes de cada pareja formada.\n");
        printf("4. Imprimir nombre y apellido de aquellas personas que quedaron solas.\n");

        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 0:
                printf("Saliendo del programa...\n");
                break;
            case 1:
                ingresarDatosPersonas(&personas, &cantidadPersonas, archivoDatosPersona);
                break;
            case 2:
                armarParejas(personas, cantidadPersonas, &parejas, &cantidadParejas, &personasSinParejas, &cantidadPersonasSinParejas);
                break;
            case 3:
                imprimirParejasFormadas(parejas, cantidadParejas, archivoParejas);
                break;
            case 4:
                imprimirPersonasSinPareja(personasSinParejas, cantidadPersonasSinParejas, archivoPersonasSinParejas);
                break;
            default:
                printf("Número de opción no válido. Intenta de nuevo.\n");
        }
    } while(opcion != 0);

    liberarMemoria(personas, cantidadPersonas, parejas, cantidadParejas, personasSinParejas, cantidadPersonasSinParejas);
}