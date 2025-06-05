#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    using namespace std;
    srand(time(NULL));

	int num_max, num_min, intentos, numMedio;
    char opcion;
	bool encontrado = false;

    cout << "Intentare adivinar un numero que tu elijas." << endl;
    cout << "Cuando indique un numero tu deberas indicar:" << endl;
	cout << "\t= si acierto al numero que tu quieres que adivine." << endl;
    cout << "\t> si el numero que tu quieres que adivine es mayor que el que mostre." << endl;
    cout << "\t< si el numero que tu quieres que adivine es menor que el que mostre." << endl;
	cout << "Dime el numero minimo: ";
	cin >> num_min;
    cout << "Dime el numero maximo: ";
    cin >> num_max;

	intentos = ceil(log2(num_max - num_min + 1));

	cout << "\nEXCELENTE. Adivinare tu numero en no mas de " << intentos << " intentos." << endl;
	cout << "Presiona ENTER cuando quieras comenzar...";
    getchar();
    getchar();

    for (int i = 1; i <= intentos; i++)
    {
        if (num_min == num_max) 
        {
            numMedio = num_min;
            encontrado = true;
        }
        else {
		    numMedio = (num_max + num_min) / 2;
        }

        cout << "\nIntento " << i << "-> El numero es..." << numMedio << ": ";
        cin >> opcion;

        while (opcion != '>' && opcion != '<' && opcion != '=')
        {
            cout << "Respuesta no valida. Debes introducir >, < o =." << endl;
            cin >> opcion;
		}

        while (encontrado && opcion != '=')
        {
            cout << "ESTAS HACIENDO TRAMPA!!!!" << endl;
            cout << "\nIntento " << i << "-> El numero es..." << numMedio << ": ";
            cin >> opcion;
        }

        if (opcion == '>') num_min = numMedio + 1;
        else if (opcion == '<')  num_max = numMedio - 1;
        else if (opcion == '=')
        {
            cout << "GANE!!!! He adivinado tu numero en " << i << " intento(s). Ponmelo mas dificil." << endl;
            return 0;
        }
    }
}
