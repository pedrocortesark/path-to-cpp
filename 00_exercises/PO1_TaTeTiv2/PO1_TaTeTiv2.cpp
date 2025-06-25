#include <iostream>
#include <string>


int main()
{
    using namespace std;

    const char JUGADOR_O = 'O';
    const char JUGADOR_X = 'X';
    const char CELDA_VACIA = '#';
    const int NUM_FILAS = 3;
    const int NUM_COLUMNAS = 3;

	char tablero[NUM_FILAS][NUM_COLUMNAS];
	int contador = 0;
	bool ganador = false;
    string jugada;
    int fila, columna;
    char opcion;
    char contenido;

    srand(time(NULL));

    char a1 = '#';
    char a2 = '#';
    char a3 = '#';
    char b1 = '#';
    char b2 = '#';
    char b3 = '#';
    char c1 = '#';
    char c2 = '#';
    char c3 = '#';  

    

    // Inicializar la tabla
    for (int i = 0; i < NUM_FILAS; i++)
        for (int j = 0; j < NUM_COLUMNAS; j++)
            tablero[i][j] = CELDA_VACIA;
    
    // Turno aleatorio
	(rand() % 2 == 0) ? opcion = JUGADOR_X : opcion = JUGADOR_O;

	//Inicio del juego
    cout << ">> Bienvenido al juego del Ta Te Ti!" << endl;

    while (!ganador)
    {
        // Comienzo del juego (seguramene haya que meter esto en un while)
        cout << "Turno del jugador: " << opcion << endl;
        cout << "\n";
        cout << "\t\t" << "  " << "1" << " " << "2" << " " << "3" << endl;
        cout << "\t\t" << "1 " << tablero[0][0] << " " << tablero[0][1] << " " << tablero[0][2] << endl;
        cout << "\t\t" << "2 " << tablero[1][0] << " " << tablero[1][1] << " " << tablero[1][2] << endl;
        cout << "\t\t" << "3 " << tablero[2][0] << " " << tablero[2][1] << " " << tablero[2][2] << endl;
        cout << "\n";

        // Check entrada de jugador y si la celda está vacía
        do
        {
            contenido = (char)0;

            cout << ">> Por favor, ingresa tu siguiente jugada: ";
            cin >> jugada;
            fila = jugada[0] - '0';
            columna = jugada[1] - '0';

            if (fila < 1 || fila > 3 || columna < 1 || columna > 3)
            {
                cout << "Jugada invalida. Por favor, ingresa una jugada valida (ejemplo: 11, 12, 32)." << endl;
                continue;
            }

            contenido = tablero[fila - 1][columna - 1];

            if (contenido != CELDA_VACIA)
                cout << " Ingresa la posicion de una celda vacia." << endl;

        } while (contenido != CELDA_VACIA);

        // Finalizamos jugada
        tablero[fila - 1][columna - 1] = opcion;

        // Checkear si hay ganador
        for (int i = 0; i < NUM_FILAS; i++)
        {
            if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2] && tablero[i][0] != CELDA_VACIA)
            {
                ganador = true;
                break;
            }
        }

        for (int i = 0; i < NUM_COLUMNAS; i++)
        {
            if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i] && tablero[0][i] != CELDA_VACIA)
            {
                ganador = true;
                break;
            }
        }

        if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2] && tablero[1][1] != CELDA_VACIA)
            ganador = true;

        if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0] && tablero[1][1] != CELDA_VACIA)
            ganador = true;

        if (ganador)
        {
            cout << "\n";
            cout << "\t\t" << "  " << "1" << " " << "2" << " " << "3" << endl;
            cout << "\t\t" << "1 " << tablero[0][0] << " " << tablero[0][1] << " " << tablero[0][2] << endl;
            cout << "\t\t" << "2 " << tablero[1][0] << " " << tablero[1][1] << " " << tablero[1][2] << endl;
            cout << "\t\t" << "3 " << tablero[2][0] << " " << tablero[2][1] << " " << tablero[2][2] << endl;
            cout << "\n";
            cout << "FIN DE LA PARTIDA. El ganador es: " << opcion << endl;
            return 0;
        }

        // Checkear si hay casillas libres
        contador = 0;
        for (int i = 0; i < NUM_FILAS; i++)
            for (int j = 0; j < NUM_COLUMNAS; j++)
                if (tablero[i][j] == CELDA_VACIA)
                    contador++;

        if (contador == 0)
        {
            cout << "FIN DE LA PARTIDA. Nadie ha ganado." << endl;
            return 0;
        }

        // Cambiamos de jugador
        if (opcion == JUGADOR_O) opcion = JUGADOR_X;
        else opcion = JUGADOR_O;
    }
}