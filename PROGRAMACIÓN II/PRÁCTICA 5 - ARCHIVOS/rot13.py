def ej(archivo_origen, archivo_destino):
    with open(archivo_origen, 'r') as file_origen:
        lineas = file_origen.readlines()

        with open(archivo_destino, 'w') as file_destino:
            nuevas_lineas = []
            # aplicar el algoritmo a cada linea
            for linea in lineas:
                nueva_linea = ""
                for c in linea:
                    newChar = chr(ord(c) + 13 % 26)
                    if c == '\n':
                        nueva_linea += '\n'
                    else: 
                        nueva_linea += newChar
                nuevas_lineas.append(nueva_linea)


            file_destino.writelines(nuevas_lineas)


ej("test_cifrar_rot13.txt", "archivo_cifrado.txt")