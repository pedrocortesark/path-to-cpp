#include <iostream>
#include <string>

using namespace std;

const unsigned LARGO_CODIGO = 4;
const char MIN_TARJETA_VALOR = 'A';
const char MAX_TARJETA_VALOR = 'H';
const int MAX_INTENTOS = 10;

/**
 @brief Genera un c�digo al azar y lo asigna al par�metro codigo.
 El c�digo generado puede contener letras repetidas.
 @param codigo El c�digo (arreglo de caracteres) a inicializar.
**/
void generarCodigo(char codigo[LARGO_CODIGO])
{
	char posibleLetra;

	srand(time(NULL));

	for (int i = 0; i < LARGO_CODIGO; i++)
	{
		posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
		codigo[i] = posibleLetra;
	}
}

/**
 @brief Lee el codigo de la entrada estandar y lo asigna a codigo.
Adem�s retorna el valor TRUE si el codigo leido es correcto, FALSE sino.
El codigo leido puede ser incorrecto si :
* Contiene uno o mas caracteres fuera del rango.
* No contiene el largo LARGO_CODIGO.
 @param codigo El arreglo donde se asignar� el c�digo le�do desde la entrada.
 @retval TRUE si la entrada es correcta, FALSE si no lo es.
**/
bool leerCodigo(char codigo[LARGO_CODIGO])
{
	for(int i = 0; i < LARGO_CODIGO; i++)
	{
		if (codigo[i] < MIN_TARJETA_VALOR || codigo[i] > MAX_TARJETA_VALOR)
		{
			cout << "ERROR: El codigo no es valido.Ingresa otro con 4 letras entre A y H >>" << endl;
			return false;
		}
	}
	return true;
}

/**
 @brief Imprime el codigo pasado como argumento en la salida estandar.
Deja el cursor al final de esa misma l�nea.
 @param codigo El c�digo a imprimir en la salida.
**/
void imprimirCodigo(char codigo[LARGO_CODIGO])
{
	for (int i = 0; i < LARGO_CODIGO; i++)
		cout << codigo[i];
}

/**
 @brief Calcula las notas de codAdivinador en funci�n de codPensador.
Asigna los buenos y los regulares a los argumentos con el mismo nombre.
 @param codAdivinador El c�digo presentado por el adivinador.
 @param codPensador El c�digo del pensador.
 @param buenos Par�metro para recibir los buenos.
 @param regulares Par�metro para recibir los regulares.
**/
void calcularNota(char codAdivinador[LARGO_CODIGO], char codPensador[LARGO_CODIGO],
	int& buenos, int& regulares) 
{
	bool comprobacionPensador[LARGO_CODIGO] = { false, false, false, false };
	bool comprobacionAdivinador[LARGO_CODIGO] = { false, false, false, false };

	buenos = 0;
	for (int j = 0; j < LARGO_CODIGO; j++)
	{
		if (codPensador[j] == codAdivinador[j])
		{
			buenos++;
			comprobacionPensador[j] = true;
			comprobacionAdivinador[j] = true;
		}
	}

	if (buenos == LARGO_CODIGO)
	{
		regulares = 0;
		return;
	}

	//Check letras acertadas pero mal colocadas
	regulares = 0;
	for (int k = 0; k < LARGO_CODIGO; k++)
	{
		if (!comprobacionAdivinador[k])
		{
			for (int l = 0; l < LARGO_CODIGO; l++)
			{
				if (!comprobacionPensador[l] && codPensador[l] == codAdivinador[k])
				{
					regulares++;
					comprobacionAdivinador[k] = true;
					comprobacionPensador[l] = true;
					break;
				}
			}
		}
	}

	cout << "<< B: " << buenos << " R: " << regulares << " >>\n";
}


int main()
{
	char codigoPensador[LARGO_CODIGO], codigoAdivinador[LARGO_CODIGO];
	int b, r;

	generarCodigo(codigoPensador);

	cout << "MasterMind V2.5\n";
	cout << "Dispones de 10 intentos para adivinar el codigo.\n" << endl;

	for (int i = 0; i < MAX_INTENTOS; i++)
	{
		
		do {
			cout << "\n<< Codigo " << i + 1 << " de " << MAX_INTENTOS << " >> ";
			cin >> codigoAdivinador;
		}
		while (!leerCodigo(codigoAdivinador));

		calcularNota(codigoAdivinador, codigoPensador, b, r);

		if (b == LARGO_CODIGO)
		{
			cout << "\n<< Has acertado el codigo! >>\n";
			return 0;
		}
	}

	cout << "\n<< Has agotado los intentos. El codigo era: ";
	imprimirCodigo(codigoPensador);
}