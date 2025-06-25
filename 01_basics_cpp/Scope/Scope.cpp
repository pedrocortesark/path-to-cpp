#include <iostream>

using namespace std;

//const int NUMBER = 5;
//
//void showNumber()
//{
//	cout << "Number: " << NUMBER << endl;
//}


int width, length, area, perimeter;

int calcPerimeter()
{
	return 2 * width + 2 * length;
}

int calcArea(int width, int length)
{
	/* Access the global and local variables */
	cout << "Global width: " << ::width << endl;
	cout << "Local width: " << width << endl;

	return width * length;
}

int main()
{
	//const int NUMBER = 10; 

	//cout << "Number: " << NUMBER << endl;
	//showNumber();

	cout << "Enter length: ";
	cin >> length;
	
	cout << "Enter width: ";
	cin >> width;

	/* Problem with same names for both global variables and functions 
	area = area(width, length);
	perimeter = perimeter(width, length);

	cout << "Area: " << area << endl;
	cout << "Perimeter: " << perimeter << endl;
	*/

	cout << "Area: " << calcArea(10, 10) << endl;
	//cout << "Perimeter: " << calcPerimeter() << endl;
}
