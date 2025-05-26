#include <iostream>

int main()
{
    using namespace std;

    const float PI = 3.14;
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
        cout << "Perimeter: " << length * 2 + width * 2;
    }
    else if (option == 'b')
    {
        cout << "Length: ";
        cin >> length;
        cout << "Width: ";
        cin >> width;
        cout << "Area: " << length *  width;
    }
    else if (option == 'c')
    {
        cout << "Radius: ";
        cin >> radius;
        cout << "Circumference: " << 2 * PI * radius;
    }
    else if (option == 'd')
    {
        cout << "Radius: ";
        cin >> radius;
        cout << "Area: " << PI * radius * radius;
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
