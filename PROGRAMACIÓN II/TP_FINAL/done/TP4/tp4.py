import random

class Persona:
    def __init__(self, nombre, apellido, edad, localidad):
        self.nombre = nombre
        self.apellido = apellido
        self.edad = edad
        self.localidad = localidad



def es_pareja_valida(persona1: Persona, persona2: Persona):
    if persona1.localidad != persona2.localidad:
        return False
    
    if persona1.edad < 16 and persona2.edad >= 16:
        return False
    
    if persona1.edad < 12 or persona2.edad < 12:
        return False
    
    if persona1.apellido == persona2.apellido:
        return False
    
    return True



def armar_parejas(personas, parejas, personas_sin_pareja, cantidad_personas, cantidad_parejas, cantidad_personas_sin_pareja):
    personas_emparejadas = [False] * cantidad_personas

    with open("parejas_python.txt", "w") as archivo:
        if archivo is None:
            print("Error al abrir el archivo")
            exit()

        archivo.write("Parejas: \n")

        for i in range(cantidad_personas):
            if not personas_emparejadas[i]:
                candidato = -1
                intentos = 10
                while intentos > 0 and candidato == -1:
                    candidato = random.randint(0, cantidad_personas - 1)

                    persona2 = random.choice(personas)

                    if not personas_emparejadas[candidato] and candidato != i and es_pareja_valida(personas[i], persona2):
                        # imprimir parejas en el archivo
                        archivo.write(f"{personas[i].nombre} {personas[i].apellido} - {persona2.nombre} {persona2.apellido}\n")

                        # almacenar parejas
                        parejas.append([personas[i], persona2])

                        personas_emparejadas[i] = True
                        personas_emparejadas[candidato] = True

                        cantidad_parejas += 1
                    else:
                        candidato = -1  # Reiniciar el candidato si no se encuentra una pareja adecuada en este intento

                    intentos -= 1

        # Identificar las personas sin pareja y almacenarlas en el array
        for i in range(cantidad_personas):
            if not personas_emparejadas[i]:
                personas_sin_pareja.append(personas[i])
                cantidad_personas_sin_pareja += 1

        print("Parejas formadas.\n")
        print(f"cantidadParejas: {cantidad_parejas}")
            
            
            

def imprimir_parejas(parejas: list[list[Persona]], cantidad_parejas: int):
    if cantidad_parejas < 1:
        print("No hay parejas formadas")
        return
    
    for pareja in parejas:
        persona1, persona2 = pareja
        print(f"{persona1.nombre} {persona1.apellido} - {persona2.nombre} {persona2.apellido}")





def imprimir_personas_sin_pareja(personas_sin_pareja: list[Persona], cantidad_personas_sin_pareja: int):
    if cantidad_personas_sin_pareja < 1:
        print("No hay personas solteras")
        return
    
    for persona in personas_sin_pareja:
        print(persona.nombre)



def leerArchivo(archivo) -> list[Persona]:
    personas = []

    with open(archivo, "r") as file:
        lineas = [linea.strip() for linea in file.readlines()]
        for linea in lineas:
            nombre, apellido, edad, localidad = linea.split(", ")
            personas.append(Persona(nombre, apellido, int(edad), localidad))

    return personas
        

def main():
    archivo: list = "salida.txt"
    
    personas = leerArchivo(archivo)
    cantidad_personas = len(personas)
    [print(persona.nombre, end=" ") for persona in personas]
    
    parejas: list[list[Persona]] = []
    cantidad_parejas: int = 0

    personas_sin_pareja: list[Persona] = []
    cantidad_personas_sin_pareja: int = 0
    
    
    parejas: list[list[tuple]] = []
    cantidad_parejas: int = 0

    while True:
        print("\nMenú: ")
        print("0. Salir del programa")
        print("1. Armar parejas")
        print("2. Imprimir parejas")
        print("3. Imprimir personas sin pareja")
        
        opcion = int(input("Opcion: "))

        if opcion == 0:
            break
        elif opcion == 1:
            armar_parejas(personas, parejas, personas_sin_pareja, cantidad_personas, cantidad_parejas, cantidad_personas_sin_pareja)
        elif opcion == 2:
            imprimir_parejas(parejas, cantidad_parejas)
        elif opcion == 3:
            imprimir_personas_sin_pareja(personas_sin_pareja, cantidad_personas_sin_pareja)
        else:
            print("Opcion inválida. Intentalo de nuevo.")
            
            
    archivo.close()

if __name__ == "__main__":
    main()