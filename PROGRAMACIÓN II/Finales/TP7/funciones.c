#include "funciones.h"

FILE *obtenerArchivo(const char *nombre, const char *modo){
    FILE *fp = fopen(nombre, modo);

    if(fp == NULL){
        printf("Error al abrir el archivo \'%s\'\n", nombre);
        exit(EXIT_FAILURE);
    }

    return fp;
}

int esMatchValido(Persona *persona1, Persona *persona2){
    // verificar que la diferencia de edad sea de al menos 3 años
    if(abs(persona1->edad - persona2->edad) > 3) {
        return 0;
    }

    // verificar que no tienen el mismo apellido
    if(strcasecmp(persona1->apellido, persona2->apellido) == 0){
        return 0;
    }
    
    // verificar que las dos personas coinciden con su genero de interés (generos distintos)
    if((strcasecmp(persona1->genero_de_preferencia, persona2->genero) != 0) || (strcasecmp(persona2->genero_de_preferencia, persona1->genero) != 0)){
        return 0;
    }

    return 1;
}

void generarMatchs(Persona **personas, int cantidadPersonas, FILE *archivoMatchs){
    int *matched = (int*)malloc(sizeof(int) * cantidadPersonas);
    memset(matched, 0, sizeof(int) * cantidadPersonas);
    
    if (matched == NULL) {
        printf("Error al asignar memoria para el array 'matched'\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i<cantidadPersonas; i++){
        if(!matched[i]){
            int candidato = -1;
            for(int intentos = 0; intentos < 10 && candidato == -1; intentos++){
                candidato = rand() % cantidadPersonas;
                if(!matched[candidato] && i != candidato && esMatchValido(personas[i], personas[candidato])){
                    fprintf(archivoMatchs, "%s %s %d %s - %s %s %d %s\n", personas[i]->nombre, personas[i]->apellido, personas[i]->edad, personas[i]->pais,  personas[candidato]->nombre, personas[candidato]->apellido, personas[candidato]->edad, personas[candidato]->pais);

                    matched[i] = 1;
                    matched[candidato] = 1;
                } else {
                    candidato = -1;
                }
            }
        }
    }

    free(matched);
}

Persona *generarPersona(char persona[]){
    Persona *nuevaPersona = (Persona*)malloc(sizeof(Persona));

    if(nuevaPersona == NULL){
        printf("Error al asignar memoria a la nueva persona\n");
        return NULL;
    }

    char *token = strtok(persona, ",");
    int i = 0;

    while(token != NULL){
        while (*token == ' ' || *token == '\t') {
            token++;
        }

        switch (i) {
            case 0:
                nuevaPersona->nombre = strdup(token);
                break;
            case 1:
                nuevaPersona->apellido = strdup(token);
                break;
            case 2:
                nuevaPersona->edad = atoi(token);
                break;
            case 3:
                nuevaPersona->pais = strdup(token);
                break;
            case 4:
                nuevaPersona->genero = strdup(token);
                break;
            case 5:
                nuevaPersona->genero_de_preferencia = strdup(token);
                break;
            case 6:
                nuevaPersona->pais_de_preferencia = strdup(token);
                break;
            default:
                break;
        }
        token = strtok(NULL, ",");
        i++;
    }

    return nuevaPersona;
}

void liberarMemoriaPersona(Persona *persona){
    free(persona->nombre);
    free(persona->apellido);
    free(persona->pais);
    free(persona->genero);
    free(persona->genero_de_preferencia);
    free(persona->pais_de_preferencia);

    free(persona);
}

void liberarMemoriaPersonas(Persona **personas, int cantidadPersonas){
    for (int i = 0; i < cantidadPersonas; i++) {
        free(personas[i]->nombre);
        free(personas[i]->apellido);
        free(personas[i]->pais);
        free(personas[i]->genero);
        free(personas[i]->genero_de_preferencia);
        free(personas[i]->pais_de_preferencia);
        free(personas[i]);
    }

    free(personas);
}

void obtenerPersonas(Persona ***personas, int *cantidadPersonas, FILE *archivoPersonas, FILE *archivoUnmatched){
    char persona[100];

    while(fgets(persona, sizeof(persona), archivoPersonas) != NULL){
        persona[strcspn(persona, "\n")] = 0;

        Persona *nuevaPersona = generarPersona(persona);

        // si la persona tiene menos de 18 años, no puede hacer matching con nadie (ya que la app no lo permitiría)
        if(nuevaPersona->edad < 18){
            fprintf(archivoUnmatched, "%s %s %d %s\n", nuevaPersona->nombre, nuevaPersona->apellido, nuevaPersona->edad, nuevaPersona->pais);
            liberarMemoriaPersona(nuevaPersona);
        } else {
            *personas = (Persona**)realloc(*personas, ((*cantidadPersonas) + 1) * sizeof(Persona*));
            (*personas)[(*cantidadPersonas)] = nuevaPersona;
            (*cantidadPersonas)++;
        }
    }
}

void obtenerDatosPersonas(FILE *archivoPersonas, FILE *archivoMatchs, FILE *archivoUnmatched){
    Persona **personas = NULL;
    int cantidadPersonas = 0; // cantidad de personas para hacer match

    obtenerPersonas(&personas, &cantidadPersonas, archivoPersonas, archivoUnmatched);
    
    generarMatchs(personas, cantidadPersonas, archivoMatchs);

    liberarMemoriaPersonas(personas, cantidadPersonas);
}