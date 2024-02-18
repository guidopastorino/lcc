import unittest
from tempfile import NamedTemporaryFile
from main import *

class TestSopaDeLetras(unittest.TestCase):
    def test_generar_tablero(self):
        with NamedTemporaryFile(mode="w", delete=False) as temp_file:
            temp_file.write("6\n")
        
        tablero = generar_tablero(temp_file.name)
        tablero_esperado = [
            ['_', '_', '_', '_', '_', '_'],
            ['_', '_', '_', '_', '_', '_'],
            ['_', '_', '_', '_', '_', '_'],
            ['_', '_', '_', '_', '_', '_'],
            ['_', '_', '_', '_', '_', '_'],
            ['_', '_', '_', '_', '_', '_']
        ]

        self.assertEqual(tablero, tablero_esperado)
        
        
        
    def test_ubicar_palabra(self):
        tablero = [['_'] * 8 for _ in range(8)]

        ubicar_palabra(tablero, "leopardo", 0, 1, 1)
        ubicar_palabra(tablero, "koala", 1, 3, 4)
        
        tablero_esperado = [
            ['l', 'e', 'o', 'p', 'a', 'r', 'd', 'o'],
            ['_', '_', '_', '_', '_', '_', '_', '_'],
            ['_', '_', '_', 'k', '_', '_', '_', '_'],
            ['_', '_', '_', 'o', '_', '_', '_', '_'],
            ['_', '_', '_', 'a', '_', '_', '_', '_'],
            ['_', '_', '_', 'l', '_', '_', '_', '_'],
            ['_', '_', '_', 'a', '_', '_', '_', '_'],
            ['_', '_', '_', '_', '_', '_', '_', '_']
        ]
        
        self.assertEqual(tablero, tablero_esperado)
    
    
    
    

if __name__ == "__main__":
    unittest.main()