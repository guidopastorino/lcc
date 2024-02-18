from done.TP5.main import *
import os
import unittest

class FunctionsTest(unittest.TestCase):
    def setUp(self) -> None:
        self.personas_file_test = ""

    def tearDown(self) -> None:
        if(os.path.exists(self.personas_file_test)):
            os.remove(self.personas_file_test)
            
            
    def test_generar_personas(self):
        lineas = [['Candela', 'Perez', '16', 'Rafaela'], ['Julian', 'Fernandez', '30', 'Esperanza'], ['Rocio', 'Gomez', '14', 'Villa Gobernador GÃ¡lvez'], ['Ezequiel', 'Ortega', '27', 'Rosario'], ['Valentina', 'Lopez', '19', 'Esperanza']]

        personas = generar_personas(lineas)

        for persona in personas:
            self.assertTrue(type(persona) == Persona)


    def test_es_pareja_valida(self):
        persona1: Persona = Persona(nombre='Candela', apellido='Perez', edad=16, localidad='Rafaela')
        persona2: Persona = Persona(nombre='Julian', apellido='Fernandez', edad=30, localidad='Esperanza')
        
        self.assertFalse(es_pareja_valida(persona1, persona2))
        
        
if __name__ == "__main__":
    unittest.main()