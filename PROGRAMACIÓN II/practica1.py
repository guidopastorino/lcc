def ej1(n):
    for i in range(0, n + 1, 2):
        print(i)
        

def ej3(n, m):
    pares_encontrados = 0
    num = m + 1

    while pares_encontrados < n:
        if num % 2 == 0:
            print(num)
            pares_encontrados += 1

        num += 1
        
        
def ej5(n):
    num = n
    suma = 0
    while num >= 0:
        suma += num
        num -= 1
        
    return suma



    
def ej6(n, m):
    suma = 0
    
    for i in range(n, m + 1):
        suma += i
    
    return suma



def duplica(name):
    return name * 2




def duplica_n(name, n):
    return name * n




def suma(a, b):
    return a + b



def resta(a, b):
    return a - b



def multiplicacion(a, b):
    return a * b



def division(a, b):
    return a // b



def ej9_e():
    operaciones = ["sumar", "restar", "multiplicar", "dividir"]
    
    while True:
        opcion = int(input('''
Elija una de las siguientes opciones para realizar su operación, en caso que no desee, puede salir.
    1. Suma
    2. Resta
    3. Multiplica
    4. Divide
    5. Salir
'''))
        
        if opcion == 5:
            print("Has salido del programa")
            break

        num1 = int(input(f"Primer número para {operaciones[opcion - 1]}: "))
        num2 = int(input(f"Segundo número para {operaciones[opcion - 1]}: "))
        
        if opcion == 1:
            print(num1 + num2)
        elif opcion == 2:
            print(num1 - num2)
        elif opcion == 3:
            print(num1 * num2)
        else:
            print(num1 // num2)
        
        
        break