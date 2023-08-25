def posicionesMultiplo(lista, n):
    return [lista[i] for i in range(len(lista)) if i % n == 0] 


def suma_acumulada(lista):
    suma_lista = []
    suma = 0
    
    for i in lista:
        suma += i
        suma_lista.append(suma)

    return suma_lista


def elimina(lista):
    return lista[1:-1] if len(lista) > 2 else []



def ordenada(lista):
    for i in range(len(lista) - 1):
        if lista[i] > lista[i + 1]:
            return False
        
    return True



def duplicado(lista):
    return len(list(set(lista))) != len(lista)



def eliminaDuplicados(lista):
    return list(set(lista))



def elementosDistintos(lista):
    return len(lista) - len(eliminaDuplicados(lista))



def busquedaDicotomica(lst: list, target: str) -> bool:
    l, u = 0, len(lst) - 1
    
    while l <= u:
        mid = (l+u) // 2
        
        if lst[mid] == target:
            return True
        elif lst[mid] < target:
            l = mid + 1
        else:
            u = mid - 1
            
    return False



def ej9(cadena):
    for s in reversed(cadena):
        print(s)
        
        
        
def contar(l, x):
    veces = 0
    
    for s in x:
        if s == l:
            veces += 1
            
    return veces




def ej11(cadena):
    vocales = {
        'a': 0,
        'e': 0,
        'i': 0,
        'o': 0,
        'u': 0
    }
    
    for s in cadena:
        letter = s.lower()
        if letter in vocales.keys():
            vocales[letter] += 1
            
            
    return vocales




def ej12(palabras):
    lista_palabras = palabras.split(" ")
    mas_cinco_letras = 0

    for s in lista_palabras:
        if len(s) > 5:
            mas_cinco_letras += 1

    return mas_cinco_letras



