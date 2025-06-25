#include <iostream>
#include <string>

using namespace std;

const char JUGADOR_O = 'O';
const char JUGADOR_X = 'X';
const char CELDA_VACIA = '#';
const int NUM_FILAS = 3;
const int NUM_COLUMNAS = 3;

/**
    @brief      Retorna JUGADOR_O o JUGADOR_X aleatoriamente con un 50% de probabilidad.
    @retval     JUGADOR_O o JUGADOR_X, uno de ambos valores al azar.
**/
char jugadorInicial()
{
    if (rand() % 2 == 0) return JUGADOR_X;
    else return JUGADOR_O;
}

/**
@brief Asigna a todas las celdas del tablero el valor CELDA_VACIA.
@param tablero El tablero a ser inicializado.
**/
void inicializarTablero(char tablero[NUM_FILAS][NUM_COLUMNAS])
{
    for (int i = 0; i < NUM_FILAS; i++)
        for (int j = 0; j < NUM_COLUMNAS; j++)
            tablero[i][j] = CELDA_VACIA;
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
void imprimirTablero(char tablero[3][3]) 
{
    cout << "\n";
    cout << "\t\t" << "  " << "1" << " " << "2" << " " << "3" << endl;
    cout << "\t\t" << "1 " << tablero[0][0] << " " << tablero[0][1] << " " << tablero[0][2] << endl;
    cout << "\t\t" << "2 " << tablero[1][0] << " " << tablero[1][1] << " " << tablero[1][2] << endl;
    cout << "\t\t" << "3 " << tablero[2][0] << " " << tablero[2][1] << " " << tablero[2][2] << endl;
    cout << "\n";
}

/**
     @brief     Verifica si existe una fila, columna o diagonal alineada.
     @param     tablero El tablero de juego.
     @retval    TRUE si hay una fila, columna o diagonal alineada, FALSE si no.
**/
bool verificarAlineacion(char tablero[NUM_FILAS][NUM_COLUMNAS])
{
    for (int i = 0; i < NUM_FILAS; i++)
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != CELDA_VACIA)
            return true;

    for (int i = 0; i < NUM_COLUMNAS; i++)
        if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != CELDA_VACIA)
            return true;

    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[1][1] != CELDA_VACIA)
        return true;

    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[1][1] != CELDA_VACIA)
        return true;

	return false;
}

/**
    @brief      Verifica si aún hay movimientos posibles, es decir, que al menos una celda esté vacía.
    @param      tablero El tablero de juego.
    @retval     TRUE si hay al menos una celda vacía, FALSE si no.
**/
bool hayMovimientosPosibles(char tablero[NUM_FILAS][NUM_COLUMNAS])
{
    for (int i = 0; i < NUM_FILAS; i++)
        for (int j = 0; j < NUM_COLUMNAS; j++)
            if (tablero[i][j] == CELDA_VACIA)
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
bool leerCoordenadas(int& fila, int& columna)
{
    string jugada;

    cin >> jugada;
    fila = jugada[0] - '0';
    columna = jugada[1] - '0';

    if (fila < 1 || fila > 3 || columna < 1 || columna > 3)
    {
        cout << "Jugada invalida. Por favor, ingresa una jugada valida (ejemplo: 11, 12, 32)." << endl;
		return false;
    }
    else
    {
        return true;
    }
}


int main()
{
    char tablero[NUM_FILAS][NUM_COLUMNAS];
    int contador = 0;
    bool ganador = false;
    char contenido;
    int fila = 0;
    int columna = 0;
    char opcion;

    srand(time(NULL));

    // Inicializar la tabla
	inicializarTablero(tablero);

    // Turno aleatorio
	opcion = jugadorInicial();

    //Inicio del juego
    cout << ">> Bienvenido al juego del Ta Te Ti!" << endl;

    while (!ganador)
    {
        cout << "Turno del jugador: " << opcion << endl;
		imprimirTablero(tablero);

        // Check entrada de jugador y si la celda está vacía
        do
        {
            contenido = (char)0;

            while (!leerCoordenadas(fila, columna))
                cout << ">> Por favor, ingresa tu siguiente jugada: ";

            contenido = tablero[fila - 1][columna - 1];

            if (contenido != CELDA_VACIA)
                cout << " Ingresa la posicion de una celda vacia." << endl;

        } while (contenido != CELDA_VACIA);


        // Finalizamos jugada
        tablero[fila - 1][columna - 1] = opcion;

        if (verificarAlineacion(tablero))
        {
			imprimirTablero(tablero);
            cout << "FIN DE LA PARTIDA. El ganador es: " << opcion << endl;
            return 0;
        }

        if (!hayMovimientosPosibles(tablero))
        {
            cout << "FIN DE LA PARTIDA. Nadie ha ganado." << endl;
            return 0;
        }

        // Cambiamos de jugador
        if (opcion == JUGADOR_O) opcion = JUGADOR_X;
        else opcion = JUGADOR_O;
    }
}
