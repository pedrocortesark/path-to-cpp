#include "Truco.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;
using namespace Truco21;


namespace Truco21
{
	void barajarDeck(Truco& t)
	{
		srand(time(NULL));
		char posibleLetra;
		int j;

		for (int i = 0; i < MAX_TARJETAS; i++)
		{
			posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
			j = 0;
			while (j < i) {
				if (t.deck[j] == posibleLetra) {
					posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
					j = 0;
				}
				else {
					j++;
				}
			}
			t.deck[i] = posibleLetra;
		}
	}

	void mostrarCartas(const Truco& t)
	{
		for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
			cout << "\t" << t.grupo1[i] << " " << t.grupo2[i] << " " << t.grupo3[i] << endl;
	}

	char revelarCarta(const Truco& t)
	{
		return t.deck[MAX_TARJETAS / 2];
	}

	void repartirCartas(Truco& t)
	{
		for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
		{
			t.grupo1[i] = t.deck[i * MAX_GRUPOS];
			t.grupo2[i] = t.deck[i * MAX_GRUPOS + 1];
			t.grupo3[i] = t.deck[i * MAX_GRUPOS + 2];
		}
	}

	void reagruparDeck(TrucoOrden orden, Truco& t)
	{
		switch (orden)
		{
		case GRUPO1:
			for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
			{
				t.deck[i] = t.grupo2[i];
				t.deck[i + MAX_TARJETAS_GRUPO] = t.grupo1[i];
				t.deck[i + 2 * MAX_TARJETAS_GRUPO] = t.grupo3[i];
			}
			break;
		case GRUPO2:
			for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
			{
				t.deck[i] = t.grupo1[i];
				t.deck[i + MAX_TARJETAS_GRUPO] = t.grupo2[i];
				t.deck[i + 2 * MAX_TARJETAS_GRUPO] = t.grupo3[i];
			}
			break;
		case GRUPO3:
			for (int i = 0; i < MAX_TARJETAS_GRUPO; i++)
			{
				t.deck[i] = t.grupo1[i];
				t.deck[i + MAX_TARJETAS_GRUPO] = t.grupo3[i];
				t.deck[i + 2 * MAX_TARJETAS_GRUPO] = t.grupo2[i];
			}
			break;
		}
	}
}