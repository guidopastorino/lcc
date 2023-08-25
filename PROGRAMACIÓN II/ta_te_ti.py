def ta_te_ti():
    # Cómo represento el tablero?
    # Cómo represento las fichas?
    # El tablero se representará como un diccionario de clave-valor, el cual, las claves serían los números de las grillas y los valores serían las fichas
    grillas = {
        1: "1",
        2: "2",
        3: "3",
        4: "4",
        5: "5",
        6: "6",
        7: "7",
        8: "8",
        9: "9",
    }
    
    # Una vez obtenida la grilla jugada por el usuario, si esta no ha sido jugada, la almacena
    grillas_jugadas = []
    
    # cómo guardo los jugadores/turnos?
    # turno 0: Jugador 1, turno 1: Jugador 2
    turno = 0
    jugadores = ["Jugador 1", "Jugador 2"]
    
    # Símbolos que se usarán al jugar
    while True:
        jugador_1 = str(input("Simbolo con el cual jugará el jugador 1: ")).upper() or "X"
        jugador_2 = str(input("Simbolo con el cual jugará el jugador 2: ")).upper() or "O"
        
        if jugador_1.casefold() == jugador_2.casefold():
            print("Los jugadores no pueden tener los mismos símbolos.")
        else:
            break
            
    
    print(f"Jugador 1: {jugador_1}".center(20, "*"))
    print(f"Jugador 2: {jugador_2}".center(20, "*"))
    
    # Como muestro el tablero?
    def print_grilla():
        print(f'''
 {grillas[7]} | {grillas[8]} | {grillas[9]} 
------------
 {grillas[4]} | {grillas[5]} | {grillas[6]} 
------------
 {grillas[1]} | {grillas[2]} | {grillas[3]} 
    ''')


    combinaciones = [
        [1, 2, 3], [4, 5, 6], [7, 8, 9],  # Filas
        [7, 4, 1], [8, 5, 2], [9, 6, 3],  # Columnas
        [7, 5, 3], [1, 5, 9]  # Diagonales
    ]
        
        
    def check_winner():
        for comb in combinaciones:
            if grillas[comb[0]] == grillas[comb[1]] == grillas[comb[2]]:
                return True
            
        return False


    print("TA-TE-TI".center(50, "-"))

    try:
        while True:  
            print(f"Turno de {jugadores[turno]} - Jugada n°: {len(grillas_jugadas) + 1}".center(50, "-"))
            print_grilla()
            
            # Cómo me dice el usuario que casilla quiere?
            grilla = int(input("Escribe el número de cuadrilla que desee colocar: "))

            # Cómo valido la casilla?
            # Primero comprobar si no está ocupada, si no está ocupada, entonces el numero que nos indicó el jugador, lo buscamos en las claves del diccionario (representación grillas) y reemplazamos el valor por el símbolo con el que está jugando 
            if grilla in grillas_jugadas:
                print(f"La grilla {grilla} está ocupada, intenta con otra.")
            elif grilla < 1 or grilla > 9:
                print("Escribe un rango de grillas entre el 1 y 9.")
            else:
                if turno == 0:
                    grillas[grilla] = jugador_1
                else:
                    grillas[grilla] = jugador_2

                grillas_jugadas.append(grilla)
                
                # verificando posible ganador
                if len(grillas_jugadas) > 4:
                    # Cómo se cuando termina?
                    # Cuando se llega a 9 jugadas y no hubo ningún match (ganador), lo cual significa empate o cuando ya se llegó a un match y hubo un ganador                 
                    
                    winner = check_winner()
                    
                    # Cómo se quien ganó?
                    # Nos guiamos por el turno en el que se está jugando, si el turno es 0, entonces gana Jugador 1, sino gana el Jugador 2 (haciendo referencia en la lista de jugadores, llamando al jugador en base al turno)
                    if winner:
                        print(f"{jugadores[turno]} ha ganado la partida")
                        print("Tablero final".center(20, "*"))
                        print_grilla()
                        break 
                    
                    if len(grillas_jugadas) == 9:
                        print("Empate".center(30, "*"))
                        print("Ningún jugador ha ganado")
                        print_grilla()
                        break
                
                
                turno = 1 if turno == 0 else 0
                
    except ValueError:
        print("No has ingresado un número para poder ocupar su casilla")
        
        
        
        
ta_te_ti()