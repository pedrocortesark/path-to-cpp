#include <iostream>
#include <string>

using namespace std;

void imprimir(int& x)
{
    x = 10;
	cout << "Value of x in function: " << x << endl;
}

/**
	@brief  Calcule the area and perimeter of a rectangle.
	@param  length    - The length of the rectangle.
	@param  width     - The width of the rectangle.
	@param  area      - Parameter to store the area of the rectangle.
	@param  perimeter - Parameter to store the perimeter of the rectangle.
	@retval           - TRUE if the operation was successful, FALSE if length or width is not positive.
**/
bool areaPerimeter(int length, int width, int& area, int& perimeter)
{
    if (length <= 0 || width <= 0) return false;
    
    area = length * width;
    perimeter = 2 * (length + width);
    return true;
}

bool leerNumero(int& num)
{
	string input;
	cin >> input;

	for (char c : input)
		if(!isdigit(c))
			return false;
	
	num = stoi(input);
	return true;
}

void inc(int& x, int increment = 1)
{
	x = x + increment;
}

int main()
{
	//int numero = 20;
	//imprimir(numero);

	//cout << endl << "Value of numero in main: " << numero << endl;




	//int areaRectangle, perimeterRectangle;

	//int length, width;

	//do {
	//	cout << "Enter the length of the rectangle: "; cin >> length;
	//	cout << "Enter the width of the rectangle: "; cin >> width;
	//} while (!areaPerimeter(length, width, areaRectangle, perimeterRectangle));

	//cout << "Area of the rectangle: " << areaRectangle << endl;
	//cout << "Perimeter of the rectangle: " << perimeterRectangle << endl;


	//int myNum;
	//cout << "Please enter a number: ";
	//while(!leerNumero(myNum)) {
	//	cout << "Please enter a valid number: ";
	//}

	//cout << "You entered: " << myNum << endl;


	int myX = 10;
	cout << "Numer before calling inc: " << myX << endl;
	inc(myX);
	cout << "Numer after calling inc: " << myX << endl;
}