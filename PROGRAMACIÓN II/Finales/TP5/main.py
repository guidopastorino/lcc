from sys import argv
from random import randint

class Persona:
    def __init__(self, nombre: str, apellido: str, localidad: str, edad: int, genero: str, genero_de_interes: str) -> None:
        self.nombre = nombre
        self.apellido = apellido
        self.localidad = localidad
        self.edad = edad
        self.genero = genero
        self.genero_de_interes = genero_de_interes
        
        
        
def es_match_valido(persona1: Persona, persona2: Persona):
    # 1. las parejas entre un menor y un mayor de 18 años no son aceptadas
    if (persona1.edad < 18 and persona2.edad >= 18) or (persona1.edad >= 18 and persona2.edad < 18):
        return False
    
    # 2. las parejas entre un menor de 11 años y un mayor de 14 años no son aceptadas
    if (persona1.edad < 11 and persona2.edad >= 14) or (persona1.edad >= 14 and persona2.edad < 11):
        return False

    # 3. las parejas entre un menor de 15 años y un mayor de 18 años no son aceptadas
    if (persona1.edad < 15 and persona2.edad >= 18) or (persona1.edad >= 18 and persona2.edad < 15):
        return False

    # 4. una persona de 10 años o menos no puede estar en pareja
    if persona1.edad <= 10 or persona2.edad <= 10:
        return False


    # 5. el genero de cada persona de la pareja debe coincidir con el genero de interés de la restante
    if (persona1.genero != persona2.genero_de_interes or persona2.genero != persona1.genero_de_interes):
        return False

    # 6. la localidad de residencia debe ser la misma
    if persona1.localidad != persona2.localidad:
        return False

    return True



def generar_personas(lineas: list[str]):
    personas = []

    for linea in lineas:
        nombre, apellido, localidad, edad, genero, genero_de_interes = linea.split(", ")
        edad = int(edad)
        persona = Persona(nombre, apellido, localidad, edad, genero, genero_de_interes)
        personas.append(persona)

    return personas




def generar_matchs(personas: list[Persona]):
    matched: list[bool] = [False] * len(personas)

    with open(argv[2], "w", encoding="utf-8") as fileParejas, open(argv[3], "w", encoding="utf-8") as filePersonasSinPareja:
        for i in range(len(personas)):
            if not matched[i]:
                candidato = -1
                intentos = len(personas)

                while (intentos > 0 and candidato == -1):
                    candidato = randint(0, len(personas) - 1)
                    
                    if not matched[candidato] and i != candidato and es_match_valido(personas[i], personas[candidato]):
                        fileParejas.write(f"{personas[i].nombre} {personas[i].apellido} {personas[i].edad} - {personas[candidato].nombre} {personas[candidato].apellido} {personas[candidato].edad} - {personas[candidato].localidad}\n")
                        
                        matched[i] = True
                        matched[candidato] = True
                    else:
                        candidato = -1
                        intentos -= 1
                        
                        
        for i in range(len(personas)):
            if not matched[i]:
                filePersonasSinPareja.write(f"{personas[i].nombre} {personas[i].apellido} {personas[i].edad} {personas[i].localidad}\n")




def leer_archivo():
    with open(argv[1], "r", encoding="utf-8") as file:
        lineas = [linea.strip() for linea in file.readlines()]
        
        personas = generar_personas(lineas)
        
        generar_matchs(personas)
        


def main():
    if(len(argv)) < 4:
        print(f"Uso: {argv[0]} <archivo_personas> <archivo_salida_parejas> <archivo_salida_personas_sin_pareja>")
        exit(1)
        
    leer_archivo()


if __name__ == "__main__":
    main()