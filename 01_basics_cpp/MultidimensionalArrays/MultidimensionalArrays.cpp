#include <iostream>

using namespace std;

int main()
{
    char tabla[4][6];
	char letra = 'A';
	char letraBuscada;
	bool existe = false;

	for (int fila = 0; fila < 4; fila++)
	{
		for (int col = 0; col < 6; col++)
		{
			tabla[fila][col] = letra;
			letra++;
		}
	}

	for (int fila = 0; fila < 4; fila++)
	{
		for (int col = 0; col < 6; col++)
		{
			cout << tabla[fila][col] << " ";
		}
		cout << endl;
	}

	cout << "LETRA: ";
	cin >> letraBuscada;

	for (int fila = 0; fila < 4; fila++)
	{
		for (int col = 0; col < 6; col++)
		{
			if (tabla[fila][col] == letraBuscada)
			{
				existe = true;
				break;
			}
		}
		if (existe) break;
	}

	existe ? cout << "La letra " << letraBuscada << " existe en la tabla." << endl
		: cout << "La letra " << letraBuscada << " no existe en la tabla." << endl;
}

