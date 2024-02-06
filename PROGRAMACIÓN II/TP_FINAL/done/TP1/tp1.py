from random import randint

def main():
    try:
        with open("salidatps1C.txt", "r") as archivoEntrada:
            aulas = int(archivoEntrada.readline().strip())
            
            lineas = [linea.strip() for linea in archivoEntrada.readlines()]

            mapa = {}
            materia_actual = None

            for elemento in lineas:
                if any(dia in elemento for dia in ['Lunes', 'Martes', 'Miercoles', 'Jueves', 'Viernes']):
                    # Si el elemento contiene un día de la semana, es un horario asociado a la materia actual
                    if materia_actual is not None:
                        mapa[materia_actual].append(elemento)
                else:
                    # Si no es un día de la semana, asumimos que es una nueva materia
                    materia_actual = elemento
                    mapa[materia_actual] = []

            
            for horarios in mapa.values():
                for i in range(len(horarios)):
                    num_aula = randint(1, aulas)
                    horarios[i] += f" - Aula {num_aula}"


            with open("salidatp1PY.txt", "w") as archivoSalida:
                for materia, horarios in mapa.items():
                    archivoSalida.write(f"{materia}\n")
                    for horario in horarios:
                        archivoSalida.write(f"{horario}\n")    

    except FileNotFoundError as e:
        print(f"Archivo de salida en C no encontrado: '{e.filename}'")

main()

