#include "funciones.h"
#include <assert.h>

void testEsParejaValida(){
    Persona *p1 = (Persona*)malloc(sizeof(Persona));
    Persona *p2 = (Persona*)malloc(sizeof(Persona));

    p1->nombre = strdup("Fernando");
    p1->apellido = strdup("Lopez");
    p1->edad = 30;
    p1->localidad = strdup("Rosario");

    p2->nombre = strdup("Sofia");
    p2->apellido = strdup("Fernandez");
    p2->edad = 25;
    p2->localidad = strdup("Rosario");

    assert(esParejaValida(p1, p2) == 1);

    free(p1->nombre);
    free(p1->apellido);
    free(p1->localidad);
    free(p1);

    free(p2->nombre);
    free(p2->apellido);
    free(p2->localidad);
    free(p2);
}

int main(){
    testEsParejaValida();

    return 0;
}