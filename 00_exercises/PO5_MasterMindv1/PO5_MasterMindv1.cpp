#include <iostream>
#include <string>

using namespace std;

int main()
{
	const char MIN_TARJETA_VALOR = 'A';
	const char MAX_TARJETA_VALOR = 'H';
	const int MAX_LETRAS = 4;
	const int MAX_INTENTOS = 10;

	char posibleLetra;
	char codigoPensador[MAX_LETRAS],codigoAdivinador[MAX_LETRAS];
	bool comprobacionPensador[MAX_LETRAS], comprobacionAdivinador[MAX_LETRAS];
	int b, r;

	srand(time(NULL));

	for (int i = 0; i < MAX_LETRAS; i++)
	{
		posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
		int j = 0;
		while (j < i)
		{
			if (codigoPensador[j] == posibleLetra)
			{
				posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
				j = 0;
			}
			else
			{
				j++;
			}
		}
		codigoPensador[i] = posibleLetra;
	}


    cout << "MasterMind V1.0\n";
	cout << "Dispones de 10 intentos para adivinar el codigo.\n" << endl;

	//for (int i = 0; i < MAX_LETRAS; i++)
	//	cout << codigoPensador[i];
	

	for (int i = 0; i < MAX_INTENTOS; i++)
	{
		bool comprobacionPensador[MAX_LETRAS] = { false, false, false, false };
		bool comprobacionAdivinador[MAX_LETRAS] = { false, false, false, false };
		cout << "\n<< Codigo " << i + 1 << " de " << MAX_INTENTOS << " >> ";
		cin >> codigoAdivinador;

		//while(!(opcion >= MIN_TARJETA_VALOR && opcion <= MAX_TARJETA_VALOR))
		//{
		//	cout << "\nOpcion no valida. Introduce una letra entre " << MIN_TARJETA_VALOR << " y " << MAX_TARJETA_VALOR << ": ";
		//	cin >> opcion;
		//}

		//Check letras bien colocadas
		b = 0;
		for (int j = 0; j < MAX_LETRAS; j++)
		{
			if (codigoPensador[j] == codigoAdivinador[j]) 
			{
				b++;
				comprobacionPensador[j] = true; 
				comprobacionAdivinador[j] = true;
			}
		}

		if (b == MAX_LETRAS)
		{
			cout << "\n<< Has acertado el codigo! >>\n";
			return 0;
		}

		//Check letras acertadas pero mal colocadas
		r = 0;
		for (int k = 0; k < MAX_LETRAS; k++)
		{
			if (!comprobacionAdivinador[k])
			{
				for (int l = 0; l < MAX_LETRAS; l++)
				{
					if (!comprobacionPensador[l] && codigoPensador[l] == codigoAdivinador[k])
					{
						r++;
						comprobacionAdivinador[k] = true;
						comprobacionPensador[l] = true;
						break;
					}
				}
			}
		}

		cout << "<< B: " << b << " R: " << r << " >>\n";
	}

	cout << "\n<< Has agotado los intentos. El codigo era: ";
	for (int i = 0; i < MAX_LETRAS; i++)
	{
		cout << codigoPensador[i];
	}
}


