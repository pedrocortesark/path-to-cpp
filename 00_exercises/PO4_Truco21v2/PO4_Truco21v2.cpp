#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

const int MAX_TARJETAS_GRUPO = 7;
const int MAX_GRUPOS = 3;
const int MAX_TARJETAS = MAX_TARJETAS_GRUPO * MAX_GRUPOS;
const char MIN_TARJETA_VALOR = 'A';
const char MAX_TARJETA_VALOR = MAX_TARJETAS + MIN_TARJETA_VALOR - 1;

/**
	@brief Procedimiento para mostrar las cartas de los grupos.
	@param grupo1 - El primer grupo de cartas.
	@param grupo2 - El segundo grupo de cartas.
	@param grupo3 - El tercer grupo de cartas.
**/
void mostrarCartas(char grupo1[MAX_TARJETAS_GRUPO], char grupo2[MAX_TARJETAS_GRUPO], char grupo3[MAX_TARJETAS_GRUPO])
{
	for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
		cout << "\t" << grupo1[i] << " " << grupo2[i] << " " << grupo3[i] << endl;
}

void barajarDeck(char deck[MAX_TARJETAS])
{
	srand(time(NULL));
	char posibleLetra;
	int j;

	for (int i = 0; i < MAX_TARJETAS; i++)
	{
		posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
		j = 0;
		while (j < i) {
			if (deck[j] == posibleLetra) {
				posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
				j = 0;
			}
			else {
				j++;
			}
		}
		deck[i] = posibleLetra;
	}
}

void repartirCartas(char deck[MAX_TARJETAS], char grupo1[MAX_TARJETAS_GRUPO], char grupo2[MAX_TARJETAS_GRUPO], char grupo3[MAX_TARJETAS_GRUPO])
{
	for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
	{
		grupo1[i] = deck[i * MAX_GRUPOS];
		grupo2[i] = deck[i * MAX_GRUPOS + 1];
		grupo3[i] = deck[i * MAX_GRUPOS + 2];
	}
}

void reagruparDeck(char deck[MAX_TARJETAS], char primerGrupo[MAX_TARJETAS_GRUPO], char segundoGrupo[MAX_TARJETAS_GRUPO], char tercerGrupo[MAX_TARJETAS_GRUPO])
{
	for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
	{
		deck[i] = primerGrupo[i];
		deck[i + MAX_TARJETAS_GRUPO] = segundoGrupo[i];
		deck[i + 2 * MAX_TARJETAS_GRUPO] = tercerGrupo[i];
	}
}

bool esOpcionValida(char opcion)
{
	return opcion == '1' || opcion == '2' || opcion == '3';
}

char revelarCarta(char deck[MAX_TARJETAS])
{
	return deck[MAX_TARJETAS / 2];
}

int main()
{
	char grupo1[MAX_TARJETAS_GRUPO], grupo2[MAX_TARJETAS_GRUPO], grupo3[MAX_TARJETAS_GRUPO];
	char deck[MAX_TARJETAS];

	char opcion;
	int intentos;
	
	// Barajar deck al azar
	barajarDeck(deck);

	// Asignar grupos de cartas
	repartirCartas(deck, grupo1, grupo2, grupo3);

	// Iniciar juego
	cout << "Haremos " << MAX_GRUPOS << " secuencias. Empecemos\n";
	intentos = 0;

	do
	{
		intentos++;
		cout << "Secuencia " << intentos << " de " << MAX_GRUPOS << endl;
		mostrarCartas(grupo1, grupo2, grupo3);

		cout << "\nEn que grupo está tu tarjeta [1, 2, 3]: ";
		cin >> opcion;

		while (!esOpcionValida(opcion)) {
			cout << "Opcion invalida. Por favor, ingresa 1, 2 o 3: ";
			cin >> opcion;
		}

		switch (opcion)
		{
		case '1':
			reagruparDeck(deck, grupo2, grupo1, grupo3);
			break;
		case '2':
			reagruparDeck(deck, grupo1, grupo2, grupo3);
			break;
		case '3':
			reagruparDeck(deck, grupo1, grupo3, grupo2);
			break;
		}

		repartirCartas(deck, grupo1, grupo2, grupo3);


	} while (intentos < MAX_GRUPOS);

	cout << "\nTu tarjeta es: " << revelarCarta(deck) << endl;

}
