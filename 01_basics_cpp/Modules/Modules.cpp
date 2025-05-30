#include <iostream>
#include "operations.h"

using namespace std;

int main()
{
    float radius, length, width;
    char option;

    cout << "Choose an option: \n\n"
        << "a) Perimeter of the rectangle\n"
        << "b) Area of the rectangle\n"
        << "c) Perimeter of the circumference\n"
        << "d) Area of the circumference\n\n"
        << "x) Exit\n\n"
        << ">>";

    cin >> option;

    if (option == 'a')
    {
        cout << "Length: ";
        cin >> length;
        cout << "Width: ";
        cin >> width;
        cout << "Perimeter: " << Rectangle::perimeter(length, width);
    }
    else if (option == 'b')
    {
        cout << "Length: ";
        cin >> length;
        cout << "Width: ";
        cin >> width;
        cout << "Area: " << Rectangle::area(length, width);
    }
    else if (option == 'c')
    {
        cout << "Radius: ";
        cin >> radius;
        cout << "Circumference: " << Circle::circumference(radius);
    }
    else if (option == 'd')
    {
        cout << "Radius: ";
        cin >> radius;
        cout << "Area: " << Circle::area(radius);
    }
    else if (option == 'x')
    {
        return 0;
    }
    else
    {
        cout << "Error, enter a valid option.";
    }

    return 0;
}