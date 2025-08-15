#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Truco.h"

using namespace std;
using namespace Truco21;

bool esOpcionValida(char opcion)
{
	return opcion == '1' || opcion == '2' || opcion == '3';
}

int main()
{
	Truco truco;

	char opcion;
	int intentos;
	
	barajarDeck(truco);

	repartirCartas(truco);

	// Iniciar juego
	cout << "Haremos " << MAX_GRUPOS << " secuencias. Empecemos\n";
	intentos = 0;

	do
	{
		intentos++;
		cout << "Secuencia " << intentos << " de " << MAX_GRUPOS << endl;
		mostrarCartas(truco);

		cout << "\nEn que grupo está tu tarjeta [1, 2, 3]: ";
		cin >> opcion;

		while (!esOpcionValida(opcion)) {
			cout << "Opcion invalida. Por favor, ingresa 1, 2 o 3: ";
			cin >> opcion;
		}

		switch (opcion)
		{
		case '1':
			reagruparDeck(GRUPO1, truco);
			break;
		case '2':
			reagruparDeck(GRUPO2, truco);
			break;
		case '3':
			reagruparDeck(GRUPO3, truco);
			break;
		}

		repartirCartas(truco);


	} while (intentos < MAX_GRUPOS);

	cout << "\nTu tarjeta es: " << revelarCarta(truco) << endl;
}
