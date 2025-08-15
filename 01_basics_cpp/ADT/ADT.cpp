#include <iostream>
#include "Person.h"

using namespace std;

int main()
{
    ADTPerson person;

	CreatePerson("John", "Doe", 30, person);
	cout << "Person created: " << GetName(person) << " " << GetLastName(person) << ", Age: " << GetAge(person) << endl;

	ADTPerson person2;
	person2 = CreatePerson("Mary", "Doe", 15);
	cout << "Person created: " << GetName(person2) << " " << GetLastName(person2) << ", Age: " << GetAge(person2) << endl;

}
