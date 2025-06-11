#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

int main()
{
    const int MAX_TARJETAS_GRUPO = 7;
    const int MAX_GRUPOS = 3;
	const int MAX_TARJETAS = MAX_TARJETAS_GRUPO * MAX_GRUPOS;
    const char MIN_TARJETA_VALOR = 'A';
	const char MAX_TARJETA_VALOR = MAX_TARJETAS + MIN_TARJETA_VALOR - 1;

	char grupo1[MAX_TARJETAS_GRUPO], grupo2[MAX_TARJETAS_GRUPO], grupo3[MAX_TARJETAS_GRUPO];
	char deck[MAX_TARJETAS];

	char opcion;
	int intentos, j;
	char posibleLetra;

	srand(time(NULL));

	// Barajar deck al azar
	for (int i = 0; i < MAX_TARJETAS; i++)
	{
		posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
		j = 0;
		while (j < i) {
			if(deck[j] == posibleLetra) {
				posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
				j = 0;
			} else {
				j++;
			}
		}
		deck[i] = posibleLetra;
	}

	// Asignar grupos de cartas
	for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
	{
		grupo1[i] = deck[i];
		grupo2[i] = deck[i + MAX_TARJETAS_GRUPO];
		grupo3[i] = deck[i + 2 * MAX_TARJETAS_GRUPO];
	}

	cout << "Haremos " << MAX_GRUPOS << " secuencias. Empecemos\n";
	intentos = 0;

	do
	{
		intentos++;
		cout << "Secuencia " << intentos << " de " << MAX_GRUPOS << endl;
		for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
			cout << "\t" << grupo1[i] << " " << grupo2[i] << " " << grupo3[i] << endl;

		cout << "\nEn que grupo está tu tarjeta [1, 2, 3]: ";
		cin >> opcion;

		while(opcion != '1' && opcion != '2' && opcion != '3') {
			cout << "Opción inválida. Por favor, ingresa 1, 2 o 3: ";
			cin >> opcion;
		}

		switch (opcion) 
		{
			case '1':

				for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
				{
					deck[i] = grupo2[i];
					deck[i + MAX_TARJETAS_GRUPO] = grupo1[i];
					deck[i + 2 * MAX_TARJETAS_GRUPO] = grupo3[i];
				}
				
				break;
			case '2':
				
				for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
				{
					deck[i] = grupo1[i];
					deck[i + MAX_TARJETAS_GRUPO] = grupo2[i];
					deck[i + 2 * MAX_TARJETAS_GRUPO] = grupo3[i];
				}

				break;
			case '3':

				for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
				{
					deck[i] = grupo1[i];
					deck[i + MAX_TARJETAS_GRUPO] = grupo3[i];
					deck[i + 2 * MAX_TARJETAS_GRUPO] = grupo2[i];
				}

				break;
		}

		for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
		{
			grupo1[i] = deck[i* MAX_GRUPOS];
			grupo2[i] = deck[i* MAX_GRUPOS + 1];
			grupo3[i] = deck[i* MAX_GRUPOS + 2];
		}
		

	} while (intentos < MAX_GRUPOS);

	cout << "\nTu tarjeta es: " << deck[10] << endl;

}
