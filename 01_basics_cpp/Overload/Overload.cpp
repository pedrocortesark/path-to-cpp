#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

namespace Rectangle
{
	float perimeter(float length, float width)
	{
		return 2 * (length + width);
	}

	float area(float length, float width)
	{
		return length * width;
	}
}

namespace Triangle
{
	float area(float base, float height)
	{
		return 0.5 * base * height;
	}
}

namespace Circle
{
	const float PI = 3.14159;
	float perimeter(float radius)
	{
		return 2 * PI * radius;
	}
	float area(float radius)
	{
		return PI * radius * radius;
	}
}

int main()
{
	float length, width, base, height, radius;
	cout << "Enter the length: "; cin >> length;
	cout << "Enter the width: "; cin >> width;
	cout << "Enter the base: "; cin >> base;
	cout << "Enter the height: "; cin >> height;
	cout << "Enter the radius: "; cin >> radius;

	float pRect = Rectangle::perimeter(length, width);
	float aRect = Rectangle::area(length, width);

	float aTri = Triangle::area(base, height);

	float aCirc = Circle::area(radius);
	float pCirc = Circle::perimeter(radius);

	cout << "Perimeter of Rectangle: " << pRect << endl;
	cout << "Area of Rectangle: " << aRect << endl;
	cout << "Area of Triangle: " << aTri << endl;
	cout << "Area of Circle: " << aCirc << endl;
	cout << "Perimeter of Circle: " << pCirc << endl;
}
