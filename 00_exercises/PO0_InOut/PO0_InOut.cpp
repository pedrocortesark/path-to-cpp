#include <iostream>
#include <string>

int main()
{
	using namespace std;

	const float TAX = 12.5;

	string name;
	int heirs;
	int money;

    cout << "Ingresa tu nombre: ";
	cin >> name;

	cout << name << ", este es tu testamento. " << endl;
	cout << "Solo hace falta que indiques la division de tu fortuna.\n" << endl;

	cout << name << ", indica la cantidad de herederos: ";
	cin >> heirs;

	cout << "Ahora indica tu fortuna total: ";
	cin >> money;

	cout << "\nEl total de $" << money << " se distribuira como sigue:"<< endl;
	cout << "\tHEREDEROS=\t" << heirs << endl;
	cout << "\tC/U RECIBE=\t" << money/heirs << endl;
	cout << "\tA CARIDAD=\t" << money%heirs << endl;

	cout << "\nSe ha de grabar todo con el impuesto a la ganancia del " << TAX << "%:" << endl;
	cout << "\tPOR HERENCIA\t" << money / heirs << "\tIMPUESTO = " << (money/heirs) * TAX / 100 << "  \tA COBRAR: " << (money / heirs) - ((money / heirs) * TAX / 100) << endl;
	cout << "\tA CARIDAD\t" << money % heirs << "\tIMPUESTO = " << (money % heirs) * TAX / 100 << "  \tA COBRAR: " << (money % heirs) - ((money % heirs) * TAX / 100) << endl;

}