#pragma once
#ifndef  Truco.h

const int MAX_TARJETAS_GRUPO = 7;
const int MAX_GRUPOS = 3;
const int MAX_TARJETAS = MAX_TARJETAS_GRUPO * MAX_GRUPOS;
const char MIN_TARJETA_VALOR = 'A';
const char MAX_TARJETA_VALOR = MAX_TARJETAS + MIN_TARJETA_VALOR - 1;

namespace Truco21
{
	enum TrucoOrden { GRUPO1, GRUPO2, GRUPO3 };

	struct Truco
	{
		char grupo1[MAX_TARJETAS_GRUPO], grupo2[MAX_TARJETAS_GRUPO], grupo3[MAX_TARJETAS_GRUPO];
		char deck[MAX_TARJETAS];
	};

	void barajarDeck(Truco& t);

	void mostrarCartas(const Truco& t);

	char revelarCarta(const Truco& t);

	void repartirCartas(Truco& t);

	void reagruparDeck(TrucoOrden orden, Truco& t);
}

#endif
