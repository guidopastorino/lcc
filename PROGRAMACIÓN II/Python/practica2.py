def ej1():
    for i in range(10, 21):
        print(i)
        



def ej2(n):
    for j in range(n + 1):
        print()
        for k in range(j, n + 1):
            print(f"|{j}||{k}|", end=" ")




def ej4():
    cantidad = int(input("Cuantos valores desea ingresar? "))

    while cantidad > 0:
        factorial = 1
        num = int(input("Número para sacar su factorial: "))
        
        for i in range(1, num + 1):
            factorial *= i

        print(factorial)

        cantidad -= 1
    
    
        
def ej5():
    print("Farengeight   |       Celcius")
    for i in range(0, 121, 10):
        celcius = (i -32) *5/9
        print(f"{i:10}    |   {celcius:0}")
        




def ej6_sin_ecuacion(n):
    num_triangular = 0
    for i in range(1, n + 1):
        num_triangular += i
        print(f"{i}: {num_triangular}")
        


def ej6_con_ecuacion(n):
    for i in range(1, n + 1):
        num_triangular = (i * (i + 1)) // 2
        print(f"{i}: {num_triangular}")
        



def ej7():
    try:
        while True:
            num = int(input("Ingrese un número positivo: "))

            if num < 0:
                print(f"El número {num} no es un número positivo, intentalo de nuevo.")
            else:
                print("Felicitaciones! Has ingresado un número positivo")
                break
    except ValueError:
        print("El tipo de dato ingresado no es un número.")
        



def ej8():
    try:
        notas = []
    
        while True:
            continuar_preguntando = int(input('''
- Desea añadir una nota?
    1. Sí
    2. No
Su elección: '''))

            if continuar_preguntando == 1:
                nota = int(input("Cuánto es la nota?: "))
                notas.append(nota)
                
            if continuar_preguntando == 2:
                if notas == []:
                    print("El promedio de las notas es 0 (ninguna nota añadida)") 
                else:
                    suma_notas = 0
                    for i in notas:
                        suma_notas += i

                    print(f"El promedio de las {len(notas)} notas es: {suma_notas // len(notas)}")
                
                break
    except ValueError:
        print("El tipo de dato ingresado no es un número")




def ej9():
    try:
        num1 = int(input("Primer número: "))
        num2 = int(input("Segundo número: "))
        
        while True:
            if num1 < num2:
                print(f"El número {num2} es mayor que {num1}. Escribe el segundo número de nuevo:")
                num2 = int(input("Segundo número: "))
            else:
                print(f"Primer número: {num1}, segundo número: {num2}")
                break
    except ValueError:
        print("El tipo de dato ingresado no es un número. Intentalo de nuevo")
        
        
        


def ej10_a(n, m):
    multiplos_n = 0
    
    for i in range(1, m):
        if i * n < m:
            multiplos_n += 1
        else:
            return multiplos_n

        
        
def ej10_b(n, m):
    multiplos_n = 0
    num = 1
    
    while num * n < m:
        multiplos_n += 1
        num += 1
        
    return multiplos_n




def ej11_a():
    contraseña_inventada = "holamundo"
    cantidad_intentos = 5
    intento = 1

    while True:
        print(f"Intento n°: {intento}")
        contraseña_ingresada = input("Contraseña: ")

        if intento == cantidad_intentos:
            print("Contraseña incorrecta. Se te han acabado los intentos.")
            break
        elif contraseña_inventada != contraseña_ingresada:
            print(False)
        else:
            print(True)
            break
        
        intento += 1





def es_primo(n):
    if n <= 1:
        return False
    
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
        
    return True



def ej12(n):
    for i in range(0, n + 1):
        if es_primo(i):
            print(i)
            



def es_potencia_de_dos(n):
    if n <= 0:
        return False
    
    while n > 1:
        if n % 2 != 0:
            return False
        
        n = n // 2
        
        
    return True


def ej13(n, m):
    suma = 0
    for i in range(n, m):
        if es_potencia_de_dos(i):
            suma += i
            
    return suma


from random import *

def ej14_a():
    veces_lanzado = 0
    
    while True:
        dado = randint(1, 6)
        
        veces_lanzado += 1
        print(f"intento: {veces_lanzado}, dado: {dado}")
        
        if dado == 6:
            break
        
        


def ej14_b(n):
    dados = {}
    intentos = n
    while n > 0:
        dado = randint(1, 6)

        if dado in dados.keys():
            dados[dado] += 1
        else:
            dados[dado] = 1

        n -= 1
    
    print(f" En {intentos} intentos ".center(25, "~"))
    for key, value in dados.items():
        if value == 1:
            print(f"El dado {key} se lanzó {value} vez.")
        else:
            print(f"El dado {key} se lanzó {value} veces.")





def ej14_c(n):
    # 6: gana 4 pesos
    # 3: gana 1 dolar
    # 1: sigue jugando
    # 2: pierde 2 pesos
    # 4: pierde 2 pesos
    # 5: pierde 2 pesos
    
    pesos = 0
    dolares = 0
    
    while n > 0:
        dado = randint(1, 6)
        
        if dado in [2,4,5]:
            pesos -= 2
        elif dado == 3:
            dolares += 1
        elif dado == 6:
            pesos += 4
        else:
            continue
        
        n -= 1
        
        
    print(f'''
- Resultado Final:
    - Pesos: {0 if pesos <= 0 else pesos}
    - Dólares: {dolares}
''')
    
    
ej14_c(10)