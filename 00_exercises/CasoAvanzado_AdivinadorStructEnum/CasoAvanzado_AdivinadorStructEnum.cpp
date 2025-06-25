#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

int const MAX_INTENTOS_FACIL = 15;
int const MAX_INTENTOS_DIFICIL = 10;
int const NUMERO_MAXIMO_FACIL_DIFICIL = 100;
int const NUMERO_MINIMO = 10;
int const INTENTOS_MINIMOS = 10;

enum TDificultad
{
    FACIL,
    DIFICIL,
    PERSONALIZADA
};

enum TEstado {
    JUGANDO,
    GANO,
    PERDIO,
    PENDIENTE
};

enum TResultado
{
    ES_MAYOR,
    ES_IGUAL,
    ES_MENOR,
};

enum TModo {
    ADIVINADOR,
    PENSADOR
};

struct TJuego
{
	TDificultad dificultad;
	int maxIntentos;
	TEstado estado;
	int numeroSecreto;
    int intActual;
	TModo modoJuego;
    int topeMaximo;
    int topeMinimo;
};

TJuego crearJuego()
{
	TJuego nuevoJuego;
	nuevoJuego.estado = PENDIENTE;
	return nuevoJuego;
}

void inicializarJuego(TJuego& juego, TModo modo, TDificultad dificultad, int intentosMaximos = MAX_INTENTOS_FACIL, int numMaximo = NUMERO_MINIMO )
{
	juego.dificultad = dificultad;
	juego.maxIntentos = intentosMaximos;
	juego.estado = JUGANDO;
	juego.intActual = 0;
	juego.modoJuego = modo;

    if(modo == ADIVINADOR)
    {
		srand(time(NULL));
		juego.numeroSecreto = rand() % numMaximo + 1;
	}
	else
	{
		juego.topeMinimo = 1;
		juego.topeMaximo = numMaximo;
		juego.maxIntentos = ceil(log2(juego.topeMaximo - juego.topeMinimo + 1));
	}
}

int getCandidato(const TJuego &juego)
{
	return (juego.topeMaximo + juego.topeMinimo) / 2;
}

TResultado verificarNumero(int n, TJuego& juego)
{
	juego.intActual++;
	if (n == juego.numeroSecreto)
	{
		juego.estado = GANO;
	}
	else if (juego.intActual == juego.maxIntentos)
	{
		juego.estado = PERDIO;
	}

	if (n == juego.numeroSecreto)
	{
		return ES_IGUAL;
	}
	else if( n < juego.numeroSecreto)
	{
		return ES_MENOR;
	}
	else
	{
		return ES_MAYOR;
	}
}

bool verificarNumero(TResultado resultado, TJuego& juego)
{
	juego.intActual++;

	switch (resultado)
	{
		case ES_MAYOR:
			juego.topeMinimo = getCandidato(juego) + 1;
			break;
		case ES_IGUAL:
			juego.estado = GANO;
			return true;
		case ES_MENOR:
			juego.topeMaximo = getCandidato(juego) - 1;
			break;
		default:
			break;
	}
	if (juego.intActual >= juego.maxIntentos)
		juego.estado = PERDIO;
	
	if (juego.topeMinimo > juego.topeMaximo)
		return false;
	else
		return true;
}

bool tryStrToInt(const string &str, int &num)
{
	for (char digit : str)
		if(!isdigit(digit))
			return false;
	
	num = stoi(str);
	return true;
}

void reset(TJuego &juego)
{
	juego.estado = PENDIENTE;
}

int main()
{
	TJuego juego;
	char opcion;
	string entrada;
	int entradaNumero;
	TModo modoJuego;
	TDificultad dificultadJuego;
	int customMaxIntentos;
	int customMaxNumero;
	int customNumeroSecreto;
	bool trampa;

	do
	{
		cout << "Elige el modo de juego (A: Adivinador, P: Pensador): ";
		cin >> opcion;
		opcion = toupper(opcion);
		while (opcion != 'A' && opcion != 'P')
		{
			cout << "Opción inválida. Elige A o P: ";
			cin >> opcion;
			opcion = toupper(opcion);
		}

		if (opcion == 'A')
			modoJuego = ADIVINADOR;
		else
			modoJuego = PENSADOR;

		cout << "Elige la dificultad (F: Facil, D: Dificil, P: Personalizada): ";
		cin >> opcion;
		opcion = toupper(opcion);

		while (opcion != 'F' && opcion != 'D' && opcion != 'P')
		{
			cout << "Opción invalida. Elige F, D o P: ";
			cin >> opcion;
			opcion = toupper(opcion);
		}

		switch (opcion)
		{
			case 'F':
				dificultadJuego = FACIL;
				break;
			case 'D':
				dificultadJuego = DIFICIL;
				break;
			case 'P':
				dificultadJuego = PERSONALIZADA;

				cout << "Introduce el numero maximo para buscar (mayor que " << INTENTOS_MINIMOS << "): ";
				cin >> entrada;

				while (!tryStrToInt(entrada, customMaxNumero) && customMaxNumero < INTENTOS_MINIMOS)
				{
					cout << "Número inválido. Debe ser un entero mayor o igual a " << NUMERO_MINIMO << ": ";
					cin >> entrada;
				}

				if (modoJuego == ADIVINADOR)
				{
					cout << "Introduce el numero minimo de intentos (mayor que " << INTENTOS_MINIMOS << "): ";
					cin >> entrada;
					while (!tryStrToInt(entrada, customMaxIntentos) || customMaxIntentos < INTENTOS_MINIMOS)
					{
						cout << "Número inválido. Debe ser un entero mayor o igual a " << INTENTOS_MINIMOS << ": ";
						cin >> entrada;
					}
				}

				break;
			default:
				break;
		}

		juego = crearJuego();
		switch (dificultadJuego)
		{
			case FACIL:
			case DIFICIL:
				inicializarJuego(juego, modoJuego, dificultadJuego);
				break;
			case PERSONALIZADA:
				inicializarJuego(juego, modoJuego, dificultadJuego, customMaxIntentos, customMaxNumero);
				break;
			default:
				break;
		}

		// Modo adivinador
		if (juego.modoJuego == ADIVINADOR)
		{
			cout << "Dispones de " << juego.maxIntentos << " intentos para adivinar:\n";
			do
			{
				cout << "Intento " << juego.intActual + 1 << " >>";
				cin >> entrada;
				while (!tryStrToInt(entrada, entradaNumero) && entradaNumero < 0)
				{
					cout << "ERROR: ingresa un entero positivo: ";
					cin >> entrada;
				}

				switch (verificarNumero(entradaNumero, juego))
				{
					case ES_MAYOR:
						cout << "El numero es menor que " << entradaNumero << ".\n";
						break;
					case ES_MENOR:
						cout << "El numero es mayor que " << entradaNumero << ".\n";
						break;
				}

			} while (juego.estado == JUGANDO);

			if (juego.estado == GANO)
			{
				cout << "¡Felicidades! Adivinaste el número";
			}
			else if (juego.estado == PERDIO)
			{
				cout << "Lo siento, has agotado tus intentos. El número era: " << juego.numeroSecreto;
			}
		}
		// Modo pensador
		else 
		{
			cout << "Excelente, adivinare el codigo en no mas de " << juego.maxIntentos << " intentos.\n";
			do {
				cout << "Intento " << juego.intActual + 1 << " >> El numero es... " << getCandidato(juego) << ": ";
				cin >> opcion;
				while (opcion != '<' && opcion != '=' && opcion != '>') {
					cout << "Respuesta inválida. Responde con <, = o >: ";
					cin >> opcion;
				}

				switch(opcion) {
					case '=':
						trampa = !verificarNumero(ES_IGUAL, juego);
						break;
					case '<':
						trampa = !verificarNumero(ES_MENOR, juego);
						break;
					case '>':
						trampa = !verificarNumero(ES_MAYOR, juego);
						break;
				}

			} while (juego.estado == JUGANDO && !trampa);

			if (trampa)
			{
				cout << "¡Trampa! El numero secreto no puede ser adivinado con las pistas dadas.\n";
			}
			else if (juego.estado == GANO)
			{
				cout << "¡Adivine el numero!";
			}
			else if (juego.estado == PERDIO)
			{
				cout << "Lo siento, no pude adivinar el numero en " << juego.maxIntentos << " intentos.\n";
			}
		}

		cout << "¿Quieres jugar de nuevo? (S/N): ";
		cin >> opcion;
		while (opcion != 'S' && opcion != 'N')
		{
			cout << "Opción inválida. Responde S o N: ";
			cin >> opcion;
			opcion = toupper(opcion);
		}
		cout << endl;

	} while (opcion != 'N');
}