#include "funciones.h"
#include <assert.h>

void testMatchValido(){
    Persona p1 = {"Pablo", "Rodríguez", 30, "Colombia", "M", "F", "Chile"};
    Persona p2 = {"Laura", "Pérez", 28, "Perú", "F", "M", "-"};

    assert(esMatchValido(&p1, &p2) == 1);
}

void testGenerarPersona(){
    char persona[] = "Javier, Torres, 26, Guatemala, M, F, Costa de Marfil";

    Persona *p = generarPersona(persona);

    assert(strcasecmp(p->nombre, "Javier") == 0);
    assert(strcasecmp(p->apellido, "Torres") == 0);
    assert(p->edad == 26);
    assert(strcasecmp(p->pais, "Guatemala") == 0);
    assert(strcasecmp(p->genero, "M") == 0);
    assert(strcasecmp(p->genero_de_preferencia, "F") == 0);
    assert(strcasecmp(p->pais_de_preferencia, "Costa de Marfil") == 0);

    liberarMemoriaPersona(p);
}

int main(){
    testMatchValido();
    testGenerarPersona();

    return 0;
}