def ej(archivo_origen, archivo_copiar):
    with open(archivo_origen, 'r') as file:
        lineas = file.readlines()

        with open(archivo_copiar, 'w') as file_copy:
            file_copy.writelines(lineas)


ej("archivo.txt", 'archivo_copia.txt')
