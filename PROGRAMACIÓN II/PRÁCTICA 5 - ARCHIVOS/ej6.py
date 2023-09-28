def cargarDatos(archivo):
    dic = {}

    with open(archivo, 'r') as file:
        lineas = file.readlines()

        for linea in lineas:
            key_val = linea.strip().split(", ")
            key = key_val[0]
            val = key_val[1]

            if key in dic:
                dic[key].append(val)
            else:
                dic[key] = [val]

    return dic





dic = {'Clave1': ['Valor1'], 'Clave2': ['Valor2'], 'Clave3': ['Valor3'], 'Clave4': ['Valor4'], 'Clave5': ['Valor5'], 'Clave6': ['Valor6', 'Valor7']}

def guardarDatos(dic: dict, archivo):
    lineas = []
    with open(archivo, 'w') as file:
        for key, values in dic.items():
            vals_str = " ".join(values)
            linea_str = f"{key}, {vals_str} \n"
            lineas.append(linea_str)

        file.writelines(lineas)
        
