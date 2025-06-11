#include <iostream>

using namespace std;

void printSeparator(int number)
{
	for (int i = 0; i < number; i++)
	{
		cout << "*";
	}
	cout << endl;
}


int main()
{
	string name, lastName;
	int age;

	int number;
	cout << "Enter the number of times to print the separator: ";
	cin >> number;

	printSeparator(number);

	cout << "Enter your name: ";
	cin >> name;
	cout << "Enter your last name: ";
	cin >> lastName;
	cout << "Enter your age: ";
	cin >> age;

	printSeparator(number);

	cout << "Hello, " << name << " " << lastName << "! You are " << age << " years old." << endl;

	printSeparator(number);
}
