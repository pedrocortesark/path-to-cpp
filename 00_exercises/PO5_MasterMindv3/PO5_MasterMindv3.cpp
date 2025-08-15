#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const unsigned LARGO_CODIGO = 4;
const char MIN_TARJETA_VALOR = 'A';
const char MAX_TARJETA_VALOR = 'H';
const int MAX_INTENTOS = 10;

/**
 @struct TCodigo
 @brief Un c�digo de caracteres.
**/
struct TCodigo {
	char codigo[LARGO_CODIGO];
};

/**
 @struct TRegistroNota
 @brief El registro de una nota es simplemente el c�digo y las notas
que �ste ha recibido al ser evaluado.
**/
struct TRegistroNota {
	TCodigo codigo;
	short int buenos, regulares;
};

/**
 @struct THistoria
 @brief Un arreglo con tope que almacena los c�digos y las notas que
�stos han recibido, por eso cada celda del arreglo es TRegistroNota.
**/
struct THistoria {
	TRegistroNota info[MAX_INTENTOS];
	short int tope;
};


/**
 @brief Genera un c�digo al azar y lo asigna al par�metro codigo.
 El c�digo generado puede contener letras repetidas.
 @param codigo El c�digo (arreglo de caracteres) a inicializar.
**/
//void generarCodigo(char codigo[LARGO_CODIGO])
void generarCodigo(TCodigo &c)
{
	char posibleLetra;

	for (int i = 0; i < LARGO_CODIGO; i++)
	{
		posibleLetra = rand() % (MAX_TARJETA_VALOR - MIN_TARJETA_VALOR + 1) + MIN_TARJETA_VALOR;
		c.codigo[i] = posibleLetra;
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
//bool leerCodigo(char codigo[LARGO_CODIGO])
bool leerCodigo(TCodigo &c)
{
	for (int i = 0; i < LARGO_CODIGO; i++)
	{
		if (c.codigo[i] < MIN_TARJETA_VALOR || c.codigo[i] > MAX_TARJETA_VALOR)
		{
			cout << "ERROR: El codigo no es valido.Ingresa otro con 4 letras entre A y H >>" << endl;
			return false;
		}
	}
	return true;
}

/**
 @brief		Lee dos notas a la vez: B y R y retorna TRUE si son correctas o
			FALSE si no lo son.
			En caso de que las notas no sean correctas B y R quedan con el valor 0.
			El fin de linea es consumido.
			Para verificar que las notas sean correctas se contempla lo siguiente:
					1: Son valores enteros
					2: Est�n entre 0 y LARGO_CODIGO
					3: La suma de B+R no puede ser mayor que LARGO_CODIGO
					4: Si B=(LARGO_CODIGO-1) y R>=1 las notas est�n mal.
			Asigna a la variable errorMessage uno de estos dos mensajes seg�n el
			caso:
				    1 y 2: 'ERROR: Ingresa solo dos numeros enteros entre 0 y
			             	 [LARGO_CODIGO] separados por un espacio en blanco.'
			        3 y 4: 'ERROR: Las notas no son correctas, por favor verifica los
							 valores.'
 @param b Par�metro que recibe los buenos le�dos desde la entrada.
 @param r Par�metro que recibe los regulares le�dos desde la entrada.
 @param errorMessage Par�metro que recibe el mensaje de error en caso de
 que lo haya.
 @retval TRUE si se leen notas v�lidas, FALSE si no.
**/
bool leerNotas(short int& b, short int& r, string& errorMessage)
{
	string entrada;
	do {
		cout << "Ingresa las notas (B R) separadas por un espacio en blanco: ";
		getline(cin, entrada);
	} while (entrada == "");

	string buenos = "";
	string regulares = "";
	bool spaceFound = false;
	bool errorFound = false;
	for (char c : entrada)
	{
		if (isspace(c))
		{
			if (spaceFound)
			{
				errorFound = true;
				break;
			}
			else
			{
				spaceFound = true;
				continue;
			}
		}
		
		if (!isdigit(c))
		{
			errorFound = true;
		}
		else 
		{
			if(!spaceFound)
			{
				buenos += c;
			}
			else
			{
				regulares += c;
			}
		}
	}

	if (errorFound)
	{
		errorMessage = "ERROR: Las notas no son correctas, por favor verifica los valores.\n";
		b = 0;
		r = 0;
		return false;
	}
	else 
	{
		b = stoi(buenos);
		r = stoi(regulares);
	}

	if(b < 0 || r < 0 || b > LARGO_CODIGO || r > LARGO_CODIGO)
	{
		errorMessage = "ERROR: Ingresa solo dos numeros enteros entre 0 y " + to_string(LARGO_CODIGO) + " separados por un espacio en blanco.\n";
		b = 0;
		r = 0;
		return false;
	}
	if(b + r > LARGO_CODIGO)
	{
		errorMessage = "ERROR: Las notas no son correctas, por favor verifica los valores.\n";
		b = 0;
		r = 0;
		return false;
	}
	if (b == (LARGO_CODIGO - 1) && r >= 1)
	{
		errorMessage = "ERROR: Las notas no son correctas, por favor verifica los valores.\n";
		b = 0;
		r = 0;
		return false;
	}

	return true;
}

/**
 @brief					Calcula las notas de codAdivinador en funci�n de codPensador.
						Asigna los buenos y los regulares a los argumentos con el mismo nombre.
 @param codAdivinador	El c�digo presentado por qui�n intenta adivinar.
 @param codPensador		El c�digo que debe ser adivinado.
 @param buenos			Par�metro que recibe los buenos.
 @param regulares		Par�metro que recibe los regulares.
**/
//void calcularNota(char codAdivinador[LARGO_CODIGO], char codPensador[LARGO_CODIGO],int& buenos, int& regulares)
void calcularNota(const TCodigo& codAdivinador, const TCodigo& codPensador, short int& buenos, short int& regulares)
{
	bool comprobacionPensador[LARGO_CODIGO] = { false, false, false, false };
	bool comprobacionAdivinador[LARGO_CODIGO] = { false, false, false, false };

	buenos = 0;
	for (int j = 0; j < LARGO_CODIGO; j++)
	{
		if (codPensador.codigo[j] == codAdivinador.codigo[j])
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
				if (!comprobacionPensador[l] && codPensador.codigo[l] == codAdivinador.codigo[k])
				{
					regulares++;
					comprobacionAdivinador[k] = true;
					comprobacionPensador[l] = true;
					break;
				}
			}
		}
	}
}


/**
 @brief Imprime el codigo pasado como argumento en la salida estandar.
Deja el cursor al final de esa misma l�nea.
 @param codigo El c�digo a imprimir en la salida.
**/
//void imprimirCodigo(char codigo[LARGO_CODIGO])
void imprimirCodigo(TCodigo c)
{
	for (int i = 0; i < LARGO_CODIGO; i++)
		cout << c.codigo[i];
}

/**
	@brief			Genera el codigo siguiente al actual en forma circular y lo asigna
					al propio par�metro codigo.Por ejemplo :
					AAAA-- > AAAB
					ABCH-- > ABDA(En este caso H es la letra m�s grande admitida)
					HHHH-- > AAAA
	@param c		El c�digo a ser modificado.
**/
void siguienteCodigo(TCodigo& c)
{
	for (int i = LARGO_CODIGO - 1; i >= 0; i--)
	{
		if(!(c.codigo[i] % MAX_TARJETA_VALOR == 0))
		{
			c.codigo[i] = c.codigo[i] + 1;
			return;
		}
		else
		{
			c.codigo[i] = (MIN_TARJETA_VALOR - 1) + (c.codigo[i] + 1) % MAX_TARJETA_VALOR;
		}
	}
}

/**
	@brief			Crea una historia vac�a y la retorna.
	@retval			La historia vac�a.
**/
THistoria crearHistoria()
{
	THistoria h;
	h.tope = -1;
	return h;
}

/**
	 @brief		Indica si la historia h es vac�a.
	 @param h	La historia a verificar.
	 @retval	TRUE si h es una historia vac�a, FALSE si no lo es.
**/
bool esHistoriaVacia(const THistoria& h)
{
	if(h.tope == -1)
		return true;
	else
		return false;
}

/**
	 @brief		Indica si la historia h est� llena.
	 @param h	La hisotira a verificar.
	 @retval	TRUE si h ya est� llena, FALSE si no.
**/
bool esHistoriaLlena(const THistoria& h)
{
	if(h.tope == MAX_INTENTOS - 1)
		return true;
	else
		return false;
}

/**
	 @brief				Guarda en la historia un nuevo c�digo con sus respectivas notas
						asociadas.
						PRECONDICI�N:
							La historia h no est� llena.
	 @param h			La historia a verificar.
	 @param c			El c�digo a almacenar.
	 @param buenos		Los buenos a almacenar.
	 @param regulares	Los regulares a almacenar.
**/
void guardarNota(THistoria& h, const TCodigo& c, short int buenos, short int regulares)
{
	TRegistroNota registro;
	registro.codigo = c;
	registro.buenos = buenos;
	registro.regulares = regulares;

	h.tope++;
	h.info[h.tope] = registro;
}

/**
	@brief			Retorna TRUE si el c�digo pasado como argumento es apropiado para
					postular al pensador o FALSE si no lo es.Para ello se compara el c�digo
					con todos los c�digos guardados en la historia evaluando sus notas.Si
					estas notas coinciden entonces el c�digo es adecuado, si un caso falla
					entonces ya no lo ser�.
	@param c		El c�digo a verificar.
	@param h		La historia con el registro de todos los c�digos y sus notas.
	@retval			TRUE si el c�digo es factible de ser presentado, FALSE si no.
**/
bool esAdecuado(const TCodigo& c, const THistoria& h)
{
	short b, r;
	for (int i = 0; i <= h.tope; i++)
	{
		calcularNota(c, h.info[i].codigo, b, r);
		if(b != h.info[i].buenos || r != h.info[i].regulares)
			return false;
	}
	return true;
}


int main()
{
	srand(time(NULL));

	short b, r;
	TCodigo codPens;
	TCodigo codAdiv;
	string errorMessage;
	THistoria historia = crearHistoria();

	while (!esHistoriaLlena(historia)) {

		if(esHistoriaVacia(historia))
		{
			generarCodigo(codPens);
			generarCodigo(codAdiv);

			cout << "MasterMind V3\n";
			cout << "Dispones de 10 intentos para adivinar el codigo. ( ";
			imprimirCodigo(codPens);
			cout << " )\n\n";
		}

		if (codAdiv.codigo == historia.info[0].codigo.codigo)
		{
			cout << "\n<< Has hecho trampas!!\n";
			return 0;
		}

		cout << "\n<< Nota " << historia.tope + 2 << " de " << MAX_INTENTOS << " --> ";
		imprimirCodigo(codAdiv);
		cout << " >> ";

		while (!leerNotas(b, r, errorMessage))
			cout << errorMessage;

		if(b == LARGO_CODIGO) {
			cout << "\n<< Has adivinado el codigo! Felicitaciones!\n";
			imprimirCodigo(codAdiv);
			return 0;
		}
		else
		{
			guardarNota(historia, codAdiv, b, r);
		}

		do {
			siguienteCodigo(codAdiv);
		} while (!esAdecuado(codAdiv, historia));
	}

	cout << "\n<< Has agotado los intentos. El codigo era: ";
	imprimirCodigo(codPens);
}
