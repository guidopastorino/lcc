import random

class Persona:
    def __init__(self, nombre, apellido, localidad, edad, genero, genero_interes) -> None:
        self.nombre = nombre
        self.apellido = apellido
        self.localidad = localidad
        self.edad = edad
        self.genero = genero
        self.genero_interes = genero_interes


def es_pareja_valida(persona1: Persona, persona2: Persona) -> bool:
    # Las parejas entre un menor y un mayor de 18 años no son aceptadas;

    if (persona1.edad < 18 and persona2.edad > 18) or (persona1.edad > 18 and persona2.edad < 18):
        return False
    
    # las parejas entre un menor de 11 años y un mayor de 14 años no son aceptadas;
    if (persona1.edad < 11 and persona2.edad > 14) or (persona1.edad > 14 and persona2.edad < 11):
        return False

    # las parejas entre un menor de 15 años y un mayor de 18 años no son aceptadas;
    if (persona1.edad < 15 and persona2.edad > 18) or (persona1.edad > 18 and persona2.edad < 15):
        return False

    # una persona de 10 años o menos no puede estar en pareja;
    if persona1.edad < 10 or persona2.edad < 10:
        return False

    # el genero de cada persona de la pareja debe coincidir con el genero de interés de la restante;
    if (persona1.genero != persona2.genero_interes) and (persona2.genero != persona1.genero_interes):
        return False

    # la localidad de residencia debe ser la misma
    if persona1.localidad != persona2.localidad:
        return False
    
    return True


def leerArchivoPersonas(archivo: str):
    personas: list[Persona] = []

    with open(archivo, "r") as file:
        lineas = [line.strip() for line in file.readlines()]
        
        for linea in lineas:
            nombre, apellido, localidad, edad, genero, genero_interes = linea.split(", ")
            persona = Persona(nombre, apellido, localidad, int(edad), genero, genero_interes)
            personas.append(persona)
        
        file.close()
        return personas


def hacer_matchs(personas: list[Persona], cantidad_personas: int):
    if cantidad_personas < 2:
        print("No hay personas suficientes para hacer matchs")
        return
    
    with open("parejas_tp_py.txt", "w") as file_parejas, open("sin_pareja_tp_py.txt", "w") as file_sin_pareja:
        emparejado: list[bool] = [False] * cantidad_personas
    
        for i in range(cantidad_personas):
            if not emparejado[i]:
                candidato = -1
                intentos = 10
                while intentos > 0 and candidato == -1:
                    candidato = random.randint(0, cantidad_personas - 1)

                    if not emparejado[candidato] and candidato != i and es_pareja_valida(personas[i], personas[candidato]):
                        file_parejas.write(f"{personas[i].nombre}, {personas[i].apellido}, {personas[i].edad}, {personas[i].localidad} - {personas[candidato].nombre}, {personas[candidato].apellido}, {personas[candidato].edad}, {personas[candidato].localidad}\n")

                        emparejado[i] = True
                        emparejado[candidato] = True
                    else:
                        candidato = -1
                        
                    intentos -= 1

                if candidato == -1:
                    file_sin_pareja.write(f"{personas[i].nombre}, {personas[i].apellido}, {personas[i].edad}, {personas[i].localidad} - No hay pareja\n")
    
    
    

def main():
    personas: list[Persona] = leerArchivoPersonas("entrada.txt")
    cantidad_personas: int = len(personas)

    print(personas)

    hacer_matchs(personas, cantidad_personas)
    

if __name__ == "__main__":
    main()