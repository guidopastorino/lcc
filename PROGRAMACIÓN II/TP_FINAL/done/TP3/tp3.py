def cargar_tablero(archivo):
    with open(archivo, 'r') as file:
        lines = file.readlines()
        filas, columnas = map(int, lines[0].split())
        tablero = [[0] * columnas for _ in range(filas)]

        for i in range(1, len(lines)):
            fila, columna, orientacion, longitud = map(int, lines[i].split())
            for j in range(longitud):
                if orientacion == 0:  # Barco en posición horizontal
                    tablero[fila - 1][columna - 1 + j] = 1
                else:  # Barco en posición vertical
                    tablero[fila - 1 + j][columna - 1] = 1

    return tablero


def imprimir_tablero(tablero):
    [print(' '.join(map(str, fila))) for fila in tablero]


def jugar_batalla_naval(tablero, intentos):
    while intentos > 0:
        imprimir_tablero(tablero)
        print(f"Intentos restantes: {intentos}")

        fila = int(input("Ingrese la fila: "))
        columna = int(input("Ingrese la columna: "))

        if tablero[fila - 1][columna - 1] == 1:
            print("¡Has acertado!")
            tablero[fila - 1][columna - 1] = 0
            if not any(any(barco) for barco in tablero):
                print("¡Has hundido todos los barcos!")
                break
        else:
            print("¡Has fallado!")

        intentos -= 1

    if intentos == 0:
        print("¡Te has quedado sin intentos! Los barcos enemigos han ganado.")

def main():
    archivo_entrada = "salida.txt"
    tablero = cargar_tablero(archivo_entrada)
    
    intentos = len([1 for fila in tablero for celda in fila if celda == 1]) * 3
    jugar_batalla_naval(tablero, intentos)

if __name__ == "__main__":
    main()
