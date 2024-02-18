from done.TP3.main import generar_tablero, imprimir_tablero
from io import StringIO
import sys

def test_generar_tablero():
    barcos = ['1 1 0 3', '3 3 1 5', '7 7 1 2']
    filas = 8
    columnas = 8
    
    resultado_esperado = [
        [1,1,1,0,0,0,0,0],
        [0,0,0,0,0,0,0,0],
        [0,0,1,0,0,0,0,0],
        [0,0,1,0,0,0,0,0],
        [0,0,1,0,0,0,0,0],
        [0,0,1,0,0,0,0,0],
        [0,0,1,0,0,0,1,0],
        [0,0,0,0,0,0,1,0],
    ]
    
    assert resultado_esperado == generar_tablero(barcos, filas, columnas)


def test_imprimir_tablero():
    tablero = [
        [1,1,0,1,0],
        [0,0,0,1,0],
        [0,1,0,1,0],
        [0,1,0,0,0],
        [0,1,0,1,1],
    ]

    expected_output = "1 1 0 1 0\n0 0 0 1 0\n0 1 0 1 0\n0 1 0 0 0\n0 1 0 1 1\n"
    sys.stdout = StringIO()
    imprimir_tablero(tablero)
    output = sys.stdout.getvalue()

    assert expected_output == output

    sys.stdout = sys.__stdout__
    

def main():
    test_generar_tablero()
    test_imprimir_tablero()


if __name__ == "__main__":
    main()