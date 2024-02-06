def buscar_camino_afinidades(afinidades: list[list], persona1: str, persona2: str, K: int):
    def dfs(actual, destino, camino):
        if len(camino) == K + 1:  # Se cambia la condición para incluir el nodo destino en el camino
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



def main():
    with open("salida.txt", "r") as archivoEntrada:
        afinidades_a_encontrar = int(archivoEntrada.readline().strip())

        print(f"Afinidades a encontrar: {afinidades_a_encontrar}")
        
        lineas = [linea.strip() for linea in archivoEntrada.readlines()]

        index_afinidades = lineas.index('Afinidades') + 1

        afinidades = [afinidad.split(", ") for afinidad in lineas[index_afinidades::]]
        
        persona1 = "Juan Cruz"
        persona2 = "Alvaro Zanutti"
        
        resultado = buscar_camino_afinidades(afinidades, persona1, persona2, afinidades_a_encontrar)

        if resultado is not None:
            for i in range(len(resultado) - 1):
                print(f"{resultado[i]}, {resultado[i + 1]}")
        else:
            print(f"No se encontraron {afinidades_a_encontrar} afinidades para {persona1} y {persona2}")
            
            
        archivoEntrada.close()
    
    
main()