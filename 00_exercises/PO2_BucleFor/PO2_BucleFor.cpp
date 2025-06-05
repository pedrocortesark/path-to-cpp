#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    using namespace std;
    srand(time(NULL));

    const int MAX_PUNTOS = 10;
    const int RESTA_PUNTOS = 1;
    const int SUMA_PUNTOS = 2;
    const int MAX_VALOR_ALEATORIO = 10;
    const int MAX_INTENTOS = 10;

	int numero = rand() % MAX_VALOR_ALEATORIO + 1;
    int puntos = MAX_PUNTOS;
	int opcion;

    cout << "Adivina tanto como puedas. Inicias con " << MAX_PUNTOS << " puntos.\n" << endl;
    cout << "NUEVO NUMERO GENERADO entre 1 y 10" << endl;

    for (int i = 1; i <= MAX_INTENTOS; i++)
    {
        cout << numero << "Intento " << i << " de " << MAX_INTENTOS << ") Ingresa el numero: ";
        cin >> opcion;

        if (opcion == numero) 
        {
            if (i == 1) {
				puntos *= 2;
				cout << "GANASTE A LA PRIMERA: Bonificacion x2." << endl;
				cout << "Tienes " << puntos << " puntos." << endl;
                return 0;
            }

            puntos += SUMA_PUNTOS;
            cout << "ACERTASTE: Ganaste 2 puntos: " << puntos << endl;

            if(i < MAX_INTENTOS) {
                numero = rand() % 10 + 1;
                cout << "NUEVO NUMERO GENERADO entre 1 y 10" << endl;
			}
        }
        else
        {
            puntos -= RESTA_PUNTOS;
            cout << "No acertaste, pierdes 1 punto: " << puntos << endl;
        }
    }

    cout << "FIM. Tu puntaje es: " << puntos << " puntos." << endl;
}
