#include <iostream>
#include <string>
import ManagePerson;
import Persistence;

using namespace std;


int main()
{
	char option, genderOption;
	TPersistence persistence;
	TList list;

	string doc, name, lastName;
	short unsigned int age;
	TGender gender;
	TPerson person;

	initializePersistence(persistence);
	list = loadList(persistence);

	cout << "Welcome to Simple DataBase!" << endl;

	do
	{
		cout << "\nPlease choose an option:" << endl;
		cout << "1 - Add Person" << endl;
		cout << "2 - List People" << endl;
		cout << "3 - Search Person" << endl;
		cout << "4 - Save changes" << endl;
		cout << "X - Exit" << endl;

		cin >> option;
		option = toupper(option);

		switch (option)
		{
		case '1':
			// Consume the enter from the previous option
			getline(cin, doc);

			cout << "Adding a new person..." << endl;
			cout << "Please enter the person's details." << endl;
			cout << "Name: ";
			getline(cin, name);
			cout << "Last Name: ";
			getline(cin, lastName);
			cout << "Document: ";
			getline(cin, doc);
			cout << "Age: ";
			cin >> age;
			cout << "[M]ale, [F]emale, [O]ther: ";
			cin >> genderOption;

			switch (genderOption)
			{
				case 'M': gender = MALE; break;
				case 'F': gender = FEMALE; break;
				case 'O': gender = OTHER; break;
			}

			person = createPerson(doc, name, lastName, age, gender);
			addPerson(list, person);
			break;

		case '2':
			printList(list);
			break;
		case '3':
			// Consume the enter from the previous option
			getline(cin, doc);

			cout << "Please insert the doc of the person to seek" << endl;
			getline(cin, doc);

			if (!seekPerson(list, doc, person)) 
			{
				cout << "Person not found with document: " << doc << endl;
			}
			else 
			{
				cout << "Person found: " << endl;
				cout << personToString(person) << endl;
			}
			break;
		case '4':
			saveList(list, persistence);
			break;
		case 'X':
			cout << "Exiting the program." << endl;
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
			break;
		}

	} while (option != 'X');
}