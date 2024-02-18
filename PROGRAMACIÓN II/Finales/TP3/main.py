from sys import argv

def generar_tablero(barcos: list[str], filas: int, columnas: int) -> list[list[int]]:
    tablero = [[0] * columnas for _ in range(filas)]
    
    for barco in barcos:
        fila, columna, posicion, longitud = map(int, barco.split())

        if posicion == 0: # Horizontal
            for j in range(longitud):
                if 0 <= fila - 1 < filas and 0 <= columna - 1 + j < columnas:
                    tablero[fila - 1][columna - 1 + j] = 1
        else: # Vertical
            for i in range(longitud):
                if 0 <= fila - 1 + i < filas and 0 <= columna - 1 < columnas:
                    tablero[fila - 1 + i][columna - 1] = 1

    return tablero



def jugar_batalla_naval(intentos: int, tablero: list[list[int]]) -> None:
    print(" Batalla naval ".title().center(30, "-"))

    while intentos > 0:
        imprimir_tablero(tablero)
        print(f"Intentos: {intentos}")
        
        try:
            fila = int(input("Fila: "))
            columna = int(input("Columna: "))
        
            if tablero[fila - 1][columna - 1] == 1:
                tablero[fila - 1][columna - 1] = 0
                if not any(any(barco) for barco in tablero):
                    imprimir_tablero(tablero)
                    print("Eliminaste todos los barcos!")
                    break
                else: 
                    print("Asertaste!")
            else:
                print("Fallaste!")
        except ValueError:
            print("Valor de entrada no válido. Intenta de nuevo colocando un número")
        except IndexError:
            print("Ups! Se te escapó un disparo fuera del tablero. Intentalo de nuevo!")

        intentos -= 1

        

    if intentos == 0:
        imprimir_tablero(tablero)
        print("Perdiste, se te acabaron los intentos!")



def imprimir_tablero(tablero: list[list[int]]) -> None:
    [print(' '.join(map(str, fila))) for fila in tablero]



def leer_archivo(nombre_archivo: str):
    with open(nombre_archivo) as file:
        filas, columnas = map(int, file.readline().strip().split(" "))
        
        barcos = [barco.strip() for barco in file.readlines()]

        tablero = generar_tablero(barcos, filas, columnas)

        intentos = len([1 for fila in tablero for celda in fila if celda == 1]) * 3

        jugar_batalla_naval(intentos, tablero)




def main():
    if len(argv) < 2:
        print(f"Uso: {argv} <archivo_entrada>")
        exit(1)

    leer_archivo(argv[1])


if __name__ == "__main__":
    main()