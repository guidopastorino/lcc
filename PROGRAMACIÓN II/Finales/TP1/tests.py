from done.TP1.main import generar_salida, generar_aula_materia, asignar_aulas, leer_archivo
import unittest
import os

class MainTests(unittest.TestCase):
    def setUp(self):
        self.test_file_input = "test_entrada_PY.txt"
        self.test_file_output = "test_salida_PY.txt"
        

    # remover archivos en caso de que hayan sido creados
    # En caso de ver cual fue el resultado de los archivos, eliminar la funcion 'tearDown'
    def tearDown(self):
        if os.path.exists(self.test_file_input):
            os.remove(self.test_file_input)
        
        if os.path.exists(self.test_file_output):
            os.remove(self.test_file_output)
    


    ### TESTS ###

    def test_generar_salida(self):
        materias = {'Programacion I': ['Lunes 11 a 15 - Aula 1'], 'Analisis Matematico I': ['Viernes 15 a 19 - Aula 3'], 'Algebra y Geometria I': ['Martes 10 a 14 - Aula 1', 'Lunes 9 a 13 - Aula 3', 'Jueves 8 a 12 - Aula 1']}
        
        lineas_materias_expected = "Programacion I\nLunes 11 a 15 - Aula 1\nAnalisis Matematico I\nViernes 15 a 19 - Aula 3\nAlgebra y Geometria I\nMartes 10 a 14 - Aula 1\nLunes 9 a 13 - Aula 3\nJueves 8 a 12 - Aula 1\n"
        
        generar_salida(self.test_file_output, materias)
        
        with open(self.test_file_output, "r") as outputFile:
            content = outputFile.read()
            
        self.assertTrue(os.path.exists(self.test_file_output))
        self.assertEqual(lineas_materias_expected, content)
            


    def test_leer_archivo(self):
        lineas = ['5\n', 'Programacion I\n', 'Lunes 11 a 15\n', 'Programacion II\n', 'Viernes 8 a 12\n', 'Lunes 14 a 18\n', 'Miercoles 14 a 18\n']
        
        with open(self.test_file_input, "w+") as inputFile:
            inputFile.writelines(lineas)
            inputFile.seek(0)
            actual_input = inputFile.read()

        expected_input = '5\nProgramacion I\nLunes 11 a 15\nProgramacion II\nViernes 8 a 12\nLunes 14 a 18\nMiercoles 14 a 18\n'
            
        self.assertTrue(os.path.exists(self.test_file_input))
        self.assertEqual(expected_input, actual_input)
            

if __name__ == "__main__":
    unittest.main()