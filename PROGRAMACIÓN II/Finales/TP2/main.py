from sys import argv
from typing import Union


def obtener_secuencia_afinidades(afinidades, persona1, persona2, K) -> Union[list[str], None]:
    """
    * Obtiene una secuencia (camino) de longitud K en la cuales la persona de inicio (persona1) está conectada con la persona final (persona2) a través de un algoritmo 'Depth First Search'
    
    Parama: 
        * afinidades (list(list(str))): Una lista con listas de afinidades formadas por dos personas
        * persona1 (str): Persona la cual iniciará el camino
        * persona2 (str): Persona la cual Finalizará el camino
        * K (int): Cantidad de frecuencias a encontrar
        
    Retrun:
        * (list(str) | None): Si se obtuvo una secuencia de K longitud, retorna una lista con las personas que la conforman, sino, retorna None
    """

    def dfs(actual, destino, camino):
        if len(camino) > K:
            if actual == destino:
                return camino
            else:
                return None

        for vecino in grafo.get(actual, []):
            if vecino not in camino:
                resultado = dfs(vecino, destino, camino + [vecino])
                if resultado:
                    return resultado

        return None
    
    
    grafo = {}

    for a, b in afinidades:
        grafo.setdefault(a, []).append(b)
        grafo.setdefault(b, []).append(a)

    return dfs(persona1, persona2, [persona1])




def leer_archivo(nombre_archivo: str) -> None:
    """
    * Lee el archivo de entrada y genera la secuencia de afinidades a partir del número K, luego, imprime el resultado.
    
    Params:
        * nombre_archivo (str): Nombre del archivo de entrada
    """

    with open(nombre_archivo, "r") as file:
        afinidades_a_encontrar = int(file.readline().strip())

        print(f"Afinidades a encontrar: {afinidades_a_encontrar}")
        
        lineas = [linea.strip() for linea in file.readlines()]

        index_afinidades = lineas.index('Afinidades') + 1
        
        afinidades = [afinidad.split(", ") for afinidad in lineas[index_afinidades:]]

        persona1 = input("Persona 1: ")
        persona2 = input("Persona 2: ")
        
        secuencia = obtener_secuencia_afinidades(afinidades, persona1, persona2, afinidades_a_encontrar)
        
        if secuencia:
            for i in range(len(secuencia) - 1):
                print(f"{secuencia[i]} - {secuencia[i + 1]}")
        else:
            print(f"No se encontró una secuencia de {afinidades_a_encontrar} afinidades para {persona1} y {persona2}")



def main():
    if len(argv) < 2:
        print(f"Uso: {argv[0]} <archivo_entrada>")
        exit(1)
        
    leer_archivo(argv[1])


if __name__ == "__main__":
    main()