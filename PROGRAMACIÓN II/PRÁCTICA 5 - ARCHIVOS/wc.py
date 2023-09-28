def ej(archivo):
    cant_lineas = 0
    caracteres = 0
    palabras = 0

    with open(archivo, 'r') as file:
        lineas = file.readlines()
        for linea in lineas:
            palabras += len(linea.strip().split())
            cant_lineas += 1
            for c in linea:
                if c != '\n':
                    caracteres += 1

    return cant_lineas, palabras, caracteres


print(ej("archivo.txt"))
