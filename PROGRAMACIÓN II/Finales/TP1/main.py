from sys import argv
from random import randint

def generar_salida(nombre_archivo: str, materias: dict[str, list]) -> None:
    """
    Escribe la información de las materias en el archivo de salida
    
    Params:
        * nombre_archivo (str): Nombre del archivo de salida
        * materias (dict(str, list)): Diccionario con la informacion de las materias y sus horarios
    """

    with open(nombre_archivo, "w") as file:
        for materia, horarios in materias.items():
            file.write(f"{materia}\n")
            for horario in horarios:
                file.write(f"{horario}\n")
            


    
def generar_aula_materia(cantidad_aulas: int, materias: dict[str, list]) -> None:
    """
    Recibe un diccionario con las materias y les asigna, a los horarios, un aula aleatorio entre la cantidad de aulas totales
    
    Params:
        * cantidad_aulas (int): Cantidad de aulas totales
        * materias (dict(str, list)): Diccionario con la informacion de las materias y sus horarios
    """

    for horario in materias.values():
        for i in range(len(horario)):
            aula = randint(1, cantidad_aulas)
            horario[i] += f" - Aula {aula}"



def asignar_aulas(cantidad_aulas: int, lineas: list[str]) -> None:
    """
    Les asigna un aula aleatoria entre 1 y la cantidad de aulas totales a los horarios de las materias
    
    Params:
        * cantidad_aulas (int): Cantidad de aulas totales
        * materias (dict(str, list)): Diccionario con la informacion de las materias y sus horarios
    """

    materias: dict[str, list] = {}
    materia_actual: str = None
    
    
    for linea in lineas:
        if any(dia in linea for dia in ["Lunes", "Martes", "Miercoles", "Jueves", "Viernes"]):
            if materia_actual is not None:
                materias[materia_actual].append(linea)
        else:
            materia_actual = linea
            materias[materia_actual] = []


    generar_aula_materia(cantidad_aulas, materias)
    
    
    generar_salida(argv[2], materias)




def leer_archivo(nombre_archivo: str) -> None:
    """
    Lee el archivo de entrada para poder obtener la cantidad de aulas y la informacion de cada materia

    Params:
        * nombre_archivo (str): Nombre del archivo de entrada 
    """

    try:
        with open(nombre_archivo, "r") as file:
            cantidad_aulas = int(file.readline().strip())    

            lineas = [linea.strip() for linea in file.readlines()]
            
            asignar_aulas(cantidad_aulas, lineas)
    
    except FileNotFoundError as e:
        print(f"{e.strerror}: \'{e.filename}\'")
        
        


def main():
    if len(argv) < 3:
        print(f"Uso: python {argv[0]} <archivo_entrada> <archivo_salida>")
        exit(1)
        
    leer_archivo(argv[1])


if __name__ == "__main__":
    main()