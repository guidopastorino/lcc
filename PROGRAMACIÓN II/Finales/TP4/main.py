from sys import argv
from random import randint, choice

# Clase para representar una persona
class Persona:
    def __init__(self, nombre: str, apellido: str, edad: int, localidad: str) -> None:
        self.nombre = nombre
        self.apellido = apellido
        self.edad = edad
        self.localidad = localidad


def generar_personas(lineas: list[list[str]]) -> list[Persona]:
    personas: list[Persona] = []

    for linea in lineas:
        persona = Persona(linea[0], linea[1], linea[2], linea[3])
        personas.append(persona)
        
    return personas


def es_pareja_valida(persona1: Persona, persona2: Persona):
    # las personas debían estar habitando en la misma localidad
    if persona1.localidad != persona2.localidad:
        return False

    # aquellos menores de 16 años sólo podían estar unidos con alguien también menor
    if int(persona1.edad) < 16 and int(persona2.edad) >= 16:
        return False

    # los menores de 12 años no eran alcanzados por las flechas de Cupido
    if int(persona1.edad) < 12 or int(persona2.edad) < 12:
        return False

    # se buscaba evitar que dos personas del mismo apellido estén unidas
    if persona1.apellido == persona2.apellido:
        return False
    
    return True


def armar_parejas(personas: list[Persona]) -> None:
    matched: list[bool] = [False] * len(personas)
    
    parejas: list[list[Persona, Persona]] = []
    
    personas_sin_pareja: list[Persona] = []

    for i in range(len(personas)):
        if not matched[i]:
            candidato = -1
            intentos = len(personas)
            while(intentos > 0 and candidato == -1):
                candidato = randint(0, len(personas) - 1)
                
                if not matched[candidato] and i != candidato and es_pareja_valida(personas[i], personas[candidato]):
                    pareja = [personas[i], personas[candidato]]
                    parejas.append(pareja)
                    
                    matched[i] = True
                    matched[candidato] = True
                else:
                    candidato = -1
                    intentos -= 1
                    
                    
    for i in range(len(personas)):
        if not matched[i]:
            personas_sin_pareja.append(personas[i])          
    
                    
    return parejas, personas_sin_pareja





def imprimir_parejas(parejas: list[list[Persona, Persona]]) -> None:
    with open(argv[2], "w") as file:
        for pareja in parejas:
            persona1, persona2 = pareja
            file.write(f"{persona1.nombre} {persona1.apellido} {persona1.edad} {persona1.localidad} - {persona2.nombre} {persona2.apellido} {persona2.edad} {persona2.localidad}\n")





def imprimir_personas_sin_parejas(personas_sin_pareja: list[Persona]) -> None:
    with open(argv[3], "w") as file:
        for persona in personas_sin_pareja:
            file.write(f"{persona.nombre} {persona.apellido} {persona.edad} {persona.localidad}\n")





def generar_parejas(nombre_archivo: str):
    with open(nombre_archivo, "r") as file:
        lineas = [persona.strip().split(",") for persona in file.readlines()]
        
        personas = generar_personas(lineas)
        
        parejas, personas_sin_pareja = armar_parejas(personas)
        
        imprimir_parejas(parejas)
        
        imprimir_personas_sin_parejas(personas_sin_pareja)
        
        
        


def main():
    if(len(argv)) < 4:
        print(f"Uso: {argv[0]} <archivo_personas> <archivo_parejas> <archivo_personas_sin_parejas>")
        
        
    generar_parejas(argv[1])

if __name__ == "__main__":
    main()