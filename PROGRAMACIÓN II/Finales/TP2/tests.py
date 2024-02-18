from done.TP2.main import *
import unittest

class TestsAfinidades(unittest.TestCase):
    def test_secuencia_afinidades_exitosa(self):
        afinidades = [['A', 'B'], ['F', 'G'], ['K', 'N'], ['B', 'K']]
        resultado_expected = ['A', 'B', 'K', 'N']
        persona1 = 'A'
        persona2 = 'N'
        K = 3
        
        resultado = obtener_secuencia_afinidades(afinidades, persona1, persona2, K)
        
        self.assertEqual(resultado, resultado_expected)
        
        
    def test_secuencia_afinidades_none(self):
        afinidades = [['A', 'B'], ['F', 'G'], ['K', 'N'], ['B', 'K']]
        persona1 = 'A'
        persona2 = 'G'
        K = 3
        
        resultado = obtener_secuencia_afinidades(afinidades, persona1, persona2, K)
        
        self.assertIsNone(resultado)
    
    
if __name__ == "__main__":
    unittest.main()