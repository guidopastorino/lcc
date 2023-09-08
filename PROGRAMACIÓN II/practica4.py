# PRÁCTICA N° 4 - PROGRAMACIÓN II

# 1. Listas y Secuencias

from random import *


def ej1_a(lst, x):
    apariciones = 0

    for i in lst:
        if i == x:
            apariciones += 1

    return apariciones


def ej1_b(lst, x):
    i = 0
    indice = -1

    while i < len(lst):
        if lst[i] == x and indice == -1:
            indice = i

        i += 1

    return indice


def ej1_c(lst, x):
    lista_indices = []

    for i in range(len(lst)):
        if lst[i] == x:
            lista_indices.append(i)

    return lista_indices


def ej2_a(lst: list) -> int:
    max = 0

    for n in lst:
        if n > max:
            max = n

    return max


def ej2_b(lst: list) -> tuple:
    max = 0

    for n in lst:
        if n > max:
            max = n

    return (max, lst.index(max))


def ej3(lst: list, target):
    l, u = 0, len(lst) - 1

    while l <= u:
        mid = (l + u) // 2

        if lst[mid] == target:
            return mid
        elif lst[mid] < target:
            l = mid + 1
        else:
            u = mid - 1

    lst.insert(l, target)

    return lst


# 2. Diccionarios

def ej4(lst: list) -> dict:
    dic = {}

    for key, value in lst:
        if key in dic.keys():
            dic[key].append(value)
        else:
            dic[key] = [value]

    return dic


def ej5_a(cadena):
    dic = {}
    palabras = cadena.split()

    for p in palabras:
        palabra = p.lower()
        if palabra in dic.keys():
            dic[palabra] += 1
        else:
            dic[palabra] = 1

    return dic


def ej5_b(cadena):
    dic = {}

    for c in cadena:
        if c.lower() in dic.keys():
            dic[c.lower()] += 1
        else:
            dic[c.lower()] = 1

    return dic


def ej5_c(tiradas):
    dic = {}

    while tiradas > 0:
        dado1 = randint(1, 6)
        dado2 = randint(1, 6)

        suma = dado1 + dado2

        if suma in dic.keys():
            dic[suma] += 1
        else:
            dic[suma] = 1

        tiradas -= 1

    return dic


def ej6(cadena):
    dic = {}
    palabras = cadena.split()

    for palabra in palabras:
        for c in palabra:
            if c not in dic:
                dic[c] = palabra
            else:
                if len(dic[c]) < len(palabra):
                    dic[c] = palabra

    return dic


# Variable estudiantes para el ejercicio 7
estudiantes = {
    "Guido": [6, 3, 7, 9, 10],
    "Oscar": [10, 3, 10, 4, 5],
    "Pablo": [8, 1, 6, 2, 9]
}


def ej7_a(estudiante):
    return sum(estudiantes[estudiante]) // len(estudiantes[estudiante])


def ej7_b():
    return max(estudiantes, key=lambda x: sum(estudiantes[x]) // len(estudiantes[x]))




# diccionario de sinónimos ej.8
sinonimos = {
    "abreviar": ["acortar", "resumir", "sintetizar", "compendiar", "reducir", "condensar", "apurar", "acelerar", "apresurar"],
    "acceder": ["aceptar", "consentir", "ceder", "condescender", "permitir", "plegarse", "doblegarse", "Entrar", "alcanzar", "llegar"],
    "acción": ["hecho", "acto", "actuación", "labor", "trabajo", "tarea", "maniobra", "movimiento", "ejercicio", "título", "valor", "obligación"]
}


def ej8(cadena, sinonimos):
    palabras = cadena.split()

    for palabra in palabras:
        if palabra in sinonimos:
            indice_palabra = palabras.index(palabra)
            palabras.remove(palabra)
            palabras.insert(indice_palabra, sinonimos[palabra][randint(0, len(sinonimos[palabra]) - 1)])
        
    palabras_reemplazadas = " ".join(palabras)
    return palabras_reemplazadas



# diccionarios para el ejercicio 9
dict1 = {
    "Zapatillas": 9000,
    "Remeras": 2500,
    "Pantalón": 3000,
    "Medias": 500,
    "Buzo": 5000
}

dict2 = {
    "Zapatillas": 1,
    "Remeras": 4,
    "Pantalón": 2,
    "Medias": 5,
    "Buzo": 3
}


def ej9(dict1, dict2):
    monto_total = 0

    for producto, valor in dict1.items():
        monto_total += valor * dict2[producto]


    return f"El monto total de la compra sería: ${monto_total}"



# 3. Conjuntos

def ej10(lst: list):
    return list(set(lst))



def ej11(cadena1, cadena2):
    set_cadena1 = set(cadena1.lower())
    set_cadena2 = set(cadena2.lower())

    return set_cadena1 & set_cadena2



def ej12(cadena1, cadena2):
    set_cadena1 = set(cadena1)
    set_cadena2 = set(cadena2)
    
    return set_cadena1.symmetric_difference(set_cadena2)




def ej13(lst: list) -> set:
    return [i for i in range(max(lst)) if i not in lst]





# diccionario para el ej.14:
dic = {
    "Guido": [1,6,9],
    "Oscar": [10,5,9,10],
    "Alberto": [21,7,15,28,9]
}



def ej14(dic: dict) -> set:
    if not dic:
        return set()

    conjuntos_dias = [set(dias) for dias in dic.values()]
    
    dias_disponibles = set(range(1, 32))

    for dias in conjuntos_dias:
        dias_disponibles &= dias
        
    return dias_disponibles        

print(ej14(dic))