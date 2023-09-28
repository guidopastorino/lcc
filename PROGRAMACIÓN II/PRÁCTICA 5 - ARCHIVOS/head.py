def ej(archivo, N):
    with open(archivo, 'r') as file:
        lineas = file.readlines()

        if N > len(lineas):
            print("La cantidad de lineas que deseas imprimir no existen en el archivo.")
        else:
            for i in range(N):
                print(lineas[i].strip())


ej("archivo.txt", 5)