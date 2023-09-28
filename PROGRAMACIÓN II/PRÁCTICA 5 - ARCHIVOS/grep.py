def ej(expr, archivo):
    with open(archivo, 'r') as file:
        lineas = file.readlines()

        for linea in lineas:
            if linea.find(expr) != -1:
                print(linea.strip())


ej("1", "archivo.txt")