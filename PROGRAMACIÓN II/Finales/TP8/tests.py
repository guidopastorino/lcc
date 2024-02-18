from main import *
import os

def test_obtener_caracteres_cifrados():
    with open("cifrado_caracteres_test_file.txt", "w") as temp_file:
        temp_file.write("H -> Y\nO -> X\nL -> O\nA -> R")
        
    caracteres = obtener_caracteres_cifrados("cifrado_caracteres_test_file.txt")
    
    resultado_esperado = [('H', 'Y'), ('O', 'X'), ('L', 'O'), ('A', 'R')]

    assert caracteres == resultado_esperado
    
    

def test_obtener_mensaje_cifrado():
    with open("cifrado_mensaje_test_file.txt", "w") as temp_file:
        temp_file.write("YXOR")
        
    mensaje_cifrado = obtener_mensaje_cifrado("cifrado_mensaje_test_file.txt")
    mensaje_esperado = "YXOR"
    
    assert mensaje_cifrado == mensaje_esperado



def test_desencriptar_mensaje():
    caracteres = obtener_caracteres_cifrados("cifrado_caracteres_test_file.txt")
    mensaje_cifrado = obtener_mensaje_cifrado("cifrado_mensaje_test_file.txt")
    
    mensaje_desencriptado = desencriptar_mensaje(caracteres, mensaje_cifrado)
    
    assert mensaje_desencriptado == "HOLA"



# Eliminar archivos temporales que se usaron en los tests (opcional, si no se quiere eliminar, no llamar a la función, para ver los resultados de los tests en los archivos generados)
def tearDown():
    if(os.path.exists("cifrado_caracteres_test_file.txt")):
        os.remove("cifrado_caracteres_test_file.txt")
        
    if(os.path.exists("cifrado_mensaje_test_file.txt")):
        os.remove("cifrado_mensaje_test_file.txt")



def main():
    test_obtener_caracteres_cifrados()
    test_obtener_mensaje_cifrado()
    test_desencriptar_mensaje()
    tearDown()
        
        
if __name__ == "__main__":
    main()