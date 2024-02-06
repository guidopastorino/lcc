#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void imprimirTablero(char tablero[3][3]){
    printf("\n");
    printf("%c | %c | %c \n", tablero[0][0], tablero[0][1], tablero[0][2]);
    printf("---------\n");
    printf("%c | %c | %c \n", tablero[1][0], tablero[1][1], tablero[1][2]);
    printf("---------\n");
    printf("%c | %c | %c \n", tablero[2][0], tablero[2][1], tablero[2][2]);
    printf("\n");
}


char obtenerSimbolo(int jugador, char simboloNoRepetir){
    char simbolo;
    printf("Simbolo jugador %d: ", jugador);
    scanf(" %c", &simbolo);
    while(!isalpha(simbolo) || tolower(simbolo) == tolower(simboloNoRepetir)){
        simbolo = obtenerSimbolo(jugador, simboloNoRepetir);
    }
    simbolo = toupper(simbolo);
    return simbolo;
}


int jugadaValida(char tablero[3][3], int casilla, char simbolo){
    if(casilla < 1 || casilla > 9){
        printf("Número de casilla inválido\n");
        return 0;
    }

    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(tablero[i][j] == (char)(casilla + '0')){
                tablero[i][j] = simbolo;
                return 1;
            }
        }
    }

    printf("Casilla ocupada. Intentalo de nuevo.\n");
    return 0;
}


int verificarJugada(char tablero[3][3], int turno){
    imprimirTablero(tablero);

    // verificar filas
    for(int i = 0; i<3; i++){
        if(tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]){
            printf("El jugador %d ha ganado la partida!\n", turno);
            return 1;
        }
    }


    // verificar columnas
    for(int j = 0; j<3; j++){
        if(tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j]){
            printf("El jugador %d ha ganado la partida!\n", turno);
            return 1;
        }
    }


    // verificar diagonales
    if((tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) || (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0])){
        printf("El jugador %d ha ganado la partida!\n", turno);
        return 1;
    }


    // verificar empate
    int empate = 1;
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(isdigit(tablero[i][j])){
                empate = 0;
                break;
            }
        }
        if(!empate){
            break;
        }
    }

    if(empate){
        printf("La jugada ha terminado en empate\n");
        return 1;
    }

    return 0;
}


int main(){
    char tablero[3][3] = {
        {'7', '8', '9'},
        {'4', '5', '6'},
        {'1', '2', '3'},
    };

    char jugador1 = obtenerSimbolo(1, ' ');
    char jugador2 = obtenerSimbolo(2, jugador1);

    int turno = 1;
    int casilla;

    printf("TA - TE - TI\n");

    while(1){
        imprimirTablero(tablero);

        printf("Turno del jugador %d (%c): ", turno, (turno == 1) ? jugador1 : jugador2);
        scanf(" %d", &casilla);

        if(!jugadaValida(tablero, casilla, (turno == 1) ? jugador1 : jugador2)){
            continue;
        }

        int resultado = verificarJugada(tablero, turno);
        if(resultado){
            break;
        }

        turno = (turno == 1) ? 2 : 1;
    }

    return 0;
}