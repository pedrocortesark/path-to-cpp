#include <iostream>
#include <string>

using namespace std;

const char JUGADOR_O = 'O';
const char JUGADOR_X = 'X';
const char CELDA_VACIA = '#';
const int NUM_FILAS = 3;
const int NUM_COLUMNAS = 3;

/**
    @enum       EstadoJuego
    @brief      El estado del juego en un momento
                dado puede ser INICIADO, FINALIZADO (cuando
                un jugador ganó) o EMPATE (cuando nadie ganó).
**/
enum EstadoJuego { INICIADO, FINALIZADO, EMPATE };

/**
    @struct     TaTeTi
    @brief      Representa el juego del TATETI.
                Contiene el tablero de juego, el turno
                actual y el estado del juego.
**/
struct TaTeTi {
    char tablero[NUM_FILAS][NUM_COLUMNAS];
    char turno;
    EstadoJuego estado;
};

/**
    @brief      Retorna JUGADOR_O o JUGADOR_X aleatoriamente con un 50% de probabilidad.
    @retval     JUGADOR_O o JUGADOR_X, uno de ambos valores al azar.
**/
char jugadorInicial()
{
    srand(time(NULL));
    if (rand() % 2 == 0) return JUGADOR_X;
    else return JUGADOR_O;
}

/**
     @brief     Indica cuál es el jugador actual retornando JUGADOR_O o JUGADOR_X.
     @param t   El juego a consultar.
     @retval    El carácter JUGADOR_O o JUGADOR_X representando al jugador actual.
**/
char jugadorActual(const TaTeTi& t)
{
	return t.turno;
}

/**
     @brief     Indica el estado actual del juego.
     @param t   El juego cuyo estado se quiere consultar.
     @retval    El estado del juego.
**/
EstadoJuego estadoActual(const TaTeTi& t)
{
	return t.estado;
}

/**
     @brief     Inicializa el juego estableciendo todas las celdas del tablero como
                CELDA_VACIA. Además se determina al azar el turno actual JUGADOR_O o
                JUGADOR_X, y se establece el estado como INICIADO.
     @param t   El juego a inicializar.
**/
void inicializarTablero(TaTeTi &t)
{
    for (int i = 0; i < NUM_FILAS; i++)
        for (int j = 0; j < NUM_COLUMNAS; j++)
            t.tablero[i][j] = CELDA_VACIA;

	t.turno = jugadorInicial();
    t.estado = INICIADO;
}

/**
     @brief      Imprime el tablero según el formato indicado en el documento:
                                 1 2 3
                                1 # # #
                                2 # # #
                                3 # # #
                Se visualizarán las coordenadas de filas y columnas, y por supuesto
                que los símbolos utilizados serán CELDA_VACIA para las celdas vacías,
                JUGADOR_O y JUGADOR_X para las posiciones donde cada jugador ha marcado.
     @param     tablero - Un arreglo bidimensional de caracters de 3x3 que representa al tablero de juego.
**/
//void imprimirTablero(char tablero[3][3])
void imprimirTablero(TaTeTi t) 
{
    cout << "\n";
    cout << "\t\t" << "  " << "1" << " " << "2" << " " << "3" << endl;
    cout << "\t\t" << "1 " << t.tablero[0][0] << " " << t.tablero[0][1] << " " << t.tablero[0][2] << endl;
    cout << "\t\t" << "2 " << t.tablero[1][0] << " " << t.tablero[1][1] << " " << t.tablero[1][2] << endl;
    cout << "\t\t" << "3 " << t.tablero[2][0] << " " << t.tablero[2][1] << " " << t.tablero[2][2] << endl;
    cout << "\n";
}

/**
     @brief         Indica si las coordenadas dadas son válidas, es decir, que fila y
                    columna sean valores entre 0 y 2 inclusive, y que además correspondan a
                    una celda vacía.
     @param fila    La fila a verificar.
     @param columna La columna a verificar.
     @param t       El juego en el que se realiza la verificación.
     @retval        TRUE si fila y columna están entre 0 y 2 y además la celda a la
                    que hacen referencia es vacía, FALSE en cualquier otro caso.
**/
bool esCeldaValida(int fila, int columna, const TaTeTi& t)
{
    if (fila < 0 || fila > NUM_FILAS - 1 || columna < 0 || columna > NUM_COLUMNAS - 1) {
        cout << "Jugada invalida. Por favor, ingresa una jugada valida (ejemplo: 11, 12, 32)." << endl;
        return false;
    }
    if (t.tablero[fila][columna] != CELDA_VACIA) {
		cout << "La celda ya esta ocupada. Por favor, ingresa una jugada valida." << endl;
        return false;
    }
	return true;
}

/**
     @brief     Verifica si existe una fila, columna o diagonal alineada.
     @param     tablero El tablero de juego.
     @retval    TRUE si hay una fila, columna o diagonal alineada, FALSE si no.
**/
//bool verificarAlineacion(char tablero[NUM_FILAS][NUM_COLUMNAS])
bool verificarAlineacion(const TaTeTi &t)
{
    for (int i = 0; i < NUM_FILAS; i++)
        if (t.tablero[i][0] == t.tablero[i][1] && t.tablero[i][1] == t.tablero[i][2] && t.tablero[i][0] != CELDA_VACIA)
            return true;

    for (int i = 0; i < NUM_COLUMNAS; i++)
        if (t.tablero[0][i] == t.tablero[1][i] && t.tablero[1][i] == t.tablero[2][i] && t.tablero[0][i] != CELDA_VACIA)
            return true;

    if (t.tablero[0][0] == t.tablero[1][1] && t.tablero[1][1] == t.tablero[2][2] && t.tablero[1][1] != CELDA_VACIA)
        return true;

    if (t.tablero[0][2] == t.tablero[1][1] && t.tablero[1][1] == t.tablero[2][0] && t.tablero[1][1] != CELDA_VACIA)
        return true;

	return false;
}

/**
    @brief      Verifica si aún hay movimientos posibles, es decir, que al menos una celda esté vacía.
    @param      tablero El tablero de juego.
    @retval     TRUE si hay al menos una celda vacía, FALSE si no.
**/
//bool hayMovimientosPosibles(char tablero[NUM_FILAS][NUM_COLUMNAS])
bool hayMovimientosPosibles(const TaTeTi &t)
{
    for (int i = 0; i < NUM_FILAS; i++)
        for (int j = 0; j < NUM_COLUMNAS; j++)
            if (t.tablero[i][j] == CELDA_VACIA)
				return true;
	return false;
}

/**
    @brief      Lee desde la entrada estándar un valor XY donde X e Y
                son dígitos numéricos entre 0 y 9, por ejemplo: 11, 12, 93, 45, etc.
                Asigna el primer dígito al parámetro fila, y el segundo al
                parámetro columna. Si, por ejemplo, la entrada es 45 quedará
                fila = 4 y columna = 5. Si se cumplen estas condiciones se retorna TRUE. En caso de que
                la entrada no se corresonda con dos dígitos numéricos se retorna
                FALSE y no se asigna nada a los parámetros.

    @param      fila Parámetro de salida para almacenar la coordenada fila.
    @param      columna Parámetro de salida para almacenar la coordenada columna.
    @retval     TRUE si lo que se ingresa en la entrada estándar es un valor
                XY donde X e Y son dígitos enteros entre 0 y 9.

**/
bool leerCoordenadas(int& fila, int& columna, const TaTeTi &t)
{
    string jugada;
    cin >> jugada;

    for(char digit : jugada) {
        if (!isdigit(digit)) {
            cout << "Entrada invalida. Por favor, ingresa una jugada valida (ejemplo: 11, 12, 32)." << endl;
            return false;
        }
	}

	fila = stoi(jugada.substr(0, 1)) - 1;
    columna = stoi(jugada.substr(1, 1)) - 1;
	return true;
}

/**
     @brief         Realiza el movimiento del jugador actual en la celda dada por las
                    coordenadas [fila][columna]. Si luego del movimiento el jugador logró
                    una alineación se establecerá el juego como FINALIZADO; si no, en caso
                    de que no queden movimientos posibles se establecerá como EMPATE. En
                    cualquier otro caso se intercambiará el jugador y se continúa la partida.
                    PRECONDICIÓNES - Se asume que:
                            * esCeldaValida(fila,columna,t)
                            * hayMovimientosPosibles(t)
     @param fila    La fila de la celda en la que se actuará.
     @param columna La columna de la celda en la que se actuará.
     @param t       El juego en el que se modificará el tablero.
**/
void realizarMovimiento(int fila, int columna, TaTeTi& t)
{
	t.tablero[fila][columna] = t.turno;

    if(verificarAlineacion(t)) 
    {
        t.estado = FINALIZADO;
        imprimirTablero(t);
        cout << "FIN DE LA PARTIDA. El ganador es: " << t.turno << endl;
        return;
    } 
    else if (!hayMovimientosPosibles(t))
    {
        t.estado = EMPATE;
        cout << "FIN DE LA PARTIDA. Nadie ha ganado." << endl;
        return;
    }
    else
    {
        t.turno = (t.turno == JUGADOR_X) ? JUGADOR_O : JUGADOR_X;
    }
}

int main()
{
	TaTeTi juego;
    int fila = 0;
    int columna = 0;

	inicializarTablero(juego);
    cout << ">> Bienvenido al juego del Ta Te Ti!" << endl;

    while (estadoActual(juego) == INICIADO)
    {
        cout << "Turno del jugador: " << juego.turno << endl;
		imprimirTablero(juego);

        do{
            cout << ">> Por favor, ingresa tu siguiente jugada: ";
        } while (!leerCoordenadas(fila, columna, juego) || !esCeldaValida(fila, columna, juego));

		realizarMovimiento(fila, columna, juego);
    }
}
