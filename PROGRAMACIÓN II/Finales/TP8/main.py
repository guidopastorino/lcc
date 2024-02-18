from sys import argv

def obtener_caracteres_cifrados(filename: str) -> list[tuple[str, str]]:
    """
    * Lee un archivo de texto que contiene las correspondencias entre caracteres originales y cifrados.
    * Cada línea del archivo debe tener el formato 'caracter_original -> caracter_cifrado'.
    * @param filename: Nombre del archivo a abrir.
    * @return: Una lista de tuplas (caracter_original, caracter_cifrado).
    """
    with open(filename, "r") as file:
        caracteres: list[tuple[str, str]] = [tuple(linea.strip().split(" -> ")) for linea in file.readlines()]
        return caracteres



def obtener_mensaje_cifrado(filename: str) -> str:
    """
    * Lee un archivo de texto que contiene el mensaje cifrado.
    * @param filename: Nombre del archivo a abrir.
    * @return: El mensaje cifrado como una cadena.
    """
    with open(filename, "r") as file:
        return file.readline().strip()



def desencriptar_mensaje(caracteres: list[tuple[str, str]], mensaje_cifrado: str) -> str:
    """
    * Desencripta un mensaje cifrado utilizando la correspondencia de caracteres proporcionada.
    * Imprime el mensaje desencriptado en la consola.
    * @param caracteres: Una lista de tuplas (caracter_original, caracter_cifrado).
    * @param mensaje_cifrado: El mensaje cifrado que se desencriptará.
    * @return: Devuelve el mensaje desencriptado
    """
    mensaje_desencriptado = ""
    
    for char in mensaje_cifrado:
        if char.isalpha():
            encontrado = False
            for tupla in caracteres:
                if char.lower() == tupla[1].lower():
                    mensaje_desencriptado += tupla[0]
                    encontrado = True
                    break
            if not encontrado:
                mensaje_desencriptado += char
        else:
            mensaje_desencriptado += char
                    
    return mensaje_desencriptado



def main():
    """
    * Función principal del programa.
    * Verifica la cantidad correcta de argumentos de línea de comandos.
    * Obtiene la correspondencia de caracteres y el mensaje cifrado.
    * Llama a la función para desencriptar el mensaje.
    """
    if(len(argv) < 3):
        print(f"Uso: {argv[0]} <archivo_cifrado_caracteres> <archivo_mensaje_cifrado>")
        exit(1)
        
    caracteres = obtener_caracteres_cifrados(argv[1])
    mensaje_cifrado = obtener_mensaje_cifrado(argv[2])
    
    mensaje_desencriptado = desencriptar_mensaje(caracteres, mensaje_cifrado)

    print("Mensaje desencriptado:", mensaje_desencriptado)



if __name__ == "__main__":
    main()
