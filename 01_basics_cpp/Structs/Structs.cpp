#include <iostream>
#include <string>

using namespace std;

/*
    Person
        Name
        LastName
        Age
        Gender
*/

enum TGender {MALE, FEMALE, OTHER};

struct TPerson
{
    string name;
	string lastName;
    TGender gender;
	int age;
};

void printPerson(TPerson person)
{
    cout << "Name: " << person.name << endl;
    cout << "Last Name: " << person.lastName << endl;
    cout << "Age: " << person.age << endl;
}

int main()
{
	TPerson person;

	person.name = "John";
	person.lastName = "Doe";
	person.age = 30;
    person.gender = MALE;

	cout << "Name: " << person.name << endl;
}
