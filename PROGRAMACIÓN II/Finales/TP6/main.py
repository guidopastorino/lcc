from sys import argv
from random import randint

def generar_tablero(archivo: str) -> list[list[str]]:
    """
    Genera un tablero vacío a partir de las dimensiones proporcionadas en el archivo.

    Parameters:
    - archivo (str): Nombre del archivo que contiene las dimensiones del tablero.

    Returns:
    - list[list[str]]: Tablero generado.
    """

    with open(archivo, "r") as file:
        n = int(file.readline().strip())
        
        return [['_'] * n for _ in range(n)]


def obtener_palabras_diccionario(archivo: str) -> tuple[list[str], list[str]]:
    """
    Obtiene las palabras verticales y horizontales del archivo de diccionario.

    Parameters:
    - archivo (str): Nombre del archivo de diccionario.

    Returns:
    - tuple[list[str], list[str]]: Palabras verticales y horizontales.
    """
    
    with open(archivo, "r") as file:
        lineas = [linea.strip() for linea in file.readlines()]
        
        index_verticales = lineas.index('VERTICAL')
        index_horizontales = lineas.index('HORIZONTAL')
        
        palabras_verticales = [palabra for palabra in lineas[index_verticales+1:index_horizontales]]
        palabras_horizontales = [palabra for palabra in lineas[index_horizontales+1:]]
        
        return palabras_verticales, palabras_horizontales


def tiene_lugar(tablero: list[list[str]], palabra: str, posicion: int, fila: int, columna: int) -> bool:
    """
    Verifica si hay suficiente espacio en el tablero para colocar una palabra en una posición específica.

    Parameters:
    - tablero (list[list[str]]): Tablero en el que se desea colocar la palabra.
    - palabra (str): Palabra que se intenta colocar.
    - posicion (int): Posición de la palabra (0 para horizontal, 1 para vertical).
    - fila (int): Fila en la que se intenta colocar la palabra.
    - columna (int): Columna en la que se intenta colocar la palabra.

    Returns:
    - bool: True si hay suficiente espacio, False en caso contrario.
    """


    n = len(tablero)
    if posicion == 0: # Horizontal
        if columna + len(palabra) - 1 > n:
            return False
        for i in range(len(palabra)):
            if tablero[fila - 1][columna - 1 + i] != '_' and tablero[fila - 1][columna - 1 + i] != palabra[i]:
                return False
    elif posicion == 1: # Vertical
        if fila + len(palabra) - 1 > n:
            return False
        for i in range(len(palabra)):
            if tablero[fila - 1 + i][columna - 1] != '_' and tablero[fila - 1 + i][columna - 1] != palabra[i]:
                return False
    else: # Posicion no válida
        return False
    
    
    return True


def ubicar_palabra(tablero: list[list[str]], palabra: str, posicion: int, fila: int, columna: int) -> None:
    """
    Coloca una palabra en el tablero en la posición especificada.

    Parameters:
    - tablero (list[list[str]]): Tablero en el que se coloca la palabra.
    - palabra (str): Palabra que se coloca.
    - posicion (int): Posición de la palabra (0 para horizontal, 1 para vertical).
    - fila (int): Fila en la que se coloca la palabra.
    - columna (int): Columna en la que se coloca la palabra.
    """

    if posicion != 0 and posicion != 1:
        print("Número de posición no válido")
        return

    if tiene_lugar(tablero, palabra, posicion, fila, columna):
        for i in range(len(palabra)):
            if posicion == 0: # Horizontal
                tablero[fila - 1][columna - 1 + i] = palabra[i]
            else: # Vertical
                tablero[fila - 1 + i][columna - 1] = palabra[i]
    else:
        print(f"No es posible colocar la palabra {palabra} {'horizontalmente' if posicion == 0 else 'verticalmente'} en la fila {fila} columna {columna}")


def ubicar_palabra_vertical_mas_larga(tablero: list[list[str]], palabras_verticales: list[str]) -> None: 
    """
    Ubica la palabra vertical más larga en el tablero.

    Parameters:
    - tablero (list[list[str]]): Tablero en el que se coloca la palabra.
    - palabras_verticales (list[str]): Lista de palabras verticales.
    """

    palabra_vertical_mas_larga = palabras_verticales[0]

    ubicar_palabra(tablero, palabra_vertical_mas_larga, 1, 1, 1)
    
    palabras_verticales.remove(palabra_vertical_mas_larga)


def ubicar_palabras_horizontales_coincidentes(tablero: list[list[str]], palabras_horizontales: list[str]) -> None:
    """
    Ubica palabras horizontales cuyas iniciales coincidan con alguna letra de la palabra recién ubicada.

    Parameters:
    - tablero (list[list[str]]): Tablero en el que se colocan las palabras.
    - palabras_horizontales (list[str]): Lista de palabras horizontales.
    """
    
    for i in range(len(tablero)):
        for palabra in palabras_horizontales:
            if palabra[0] == tablero[i][0]:
                ubicar_palabra(tablero, palabra, 0, i + 1, 1)
                palabras_horizontales.remove(palabra)
                break


def ubicar_siguiente_palabra_vertical_mas_larga(tablero: list[list[str]], palabras_verticales: list[str]) -> None:
    """
    Ubica la siguiente palabra vertical más larga en el tablero.

    Parameters:
    - tablero (list[list[str]]): Tablero en el que se coloca la palabra.
    - palabras_verticales (list[str]): Lista de palabras verticales.
    """

    for fila in range(1, len(tablero)):
        for columna in range(1, len(tablero)):
            for palabra in palabras_verticales:
                if tiene_lugar(tablero, palabra, 1, fila, columna):
                    ubicar_palabra(tablero, palabra, 1, fila, columna)
                    palabras_verticales.remove(palabra)


def ubicar_palabras_horizontales_restantes(tablero: list[list[str]], palabras_horizontales: list[str]) -> None:
    """
    Ubica palabras horizontales restantes en el tablero.

    Parameters:
    - tablero (list[list[str]]): Tablero en el que se colocan las palabras.
    - palabras_horizontales (list[str]): Lista de palabras horizontales.
    """

    for fila in range(1, len(tablero)):
        for columna in range(1, len(tablero)):
            for palabra in palabras_horizontales:
                if tiene_lugar(tablero, palabra, 0, fila, columna):
                    ubicar_palabra(tablero, palabra, 0, fila, columna)
                    palabras_horizontales.remove(palabra)


def ubicar_palabras(tablero: list[list[str]], palabras_verticales: list[str], palabras_horizontales: list[str]) -> None:
    """
    Ubica las palabras en el tablero siguiendo un conjunto de reglas específicas.

    Parameters:
    - tablero (list[list[str]]): Tablero en el que se colocan las palabras.
    - palabras_verticales (list[str]): Lista de palabras verticales.
    - palabras_horizontales (list[str]): Lista de palabras horizontales.
    """

    palabras_verticales.sort(key=len, reverse=True)

    ubicar_palabra_vertical_mas_larga(tablero, palabras_verticales)

    ubicar_palabras_horizontales_coincidentes(tablero, palabras_horizontales)

    ubicar_siguiente_palabra_vertical_mas_larga(tablero, palabras_verticales)

    ubicar_palabras_horizontales_restantes(tablero, palabras_horizontales)


def rellenar_tablero(tablero: list[list[str]]) -> None:
    """
    Rellena las celdas vacías del tablero con letras aleatorias.

    Parameters:
    - tablero (list[list[str]]): Tablero que se va a rellenar.
    """

    for i in range(len(tablero)):
        for j in range(len(tablero)):
            if not tablero[i][j].isalpha():
                tablero[i][j] = chr(randint(ord('a'), ord('z')))


def escribir_archivo(archivo: str, tablero: list[list[str]]) -> None:
    """
    Escribe el contenido del tablero en un archivo.

    Parameters:
    - archivo (str): Nombre del archivo de salida.
    - tablero (list[list[str]]): Tablero cuyo contenido se va a escribir en el archivo.
    """

    with open(archivo, "w") as file:
        file.write('\n'.join(' '.join(map(str, fila)) for fila in tablero))


def main():
    if(len(argv) < 3):
        print(f"Uso: {argv[0]} <archivo_entrada_datos_sopa_de_letras> <archivo_salida_tablero>")
        exit(1)
        
    tablero = generar_tablero(argv[1])
    palabras_verticales, palabras_horizontales = obtener_palabras_diccionario(argv[1])

    
    ubicar_palabras(tablero, palabras_verticales, palabras_horizontales)
    
    rellenar_tablero(tablero)
    
    escribir_archivo(argv[2], tablero)


if __name__ == "__main__":
    main()