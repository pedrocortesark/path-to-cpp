
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum TGender {MALE, FEMALE, OTHER};

struct TPerson
{
    string name;
    short unsigned int age;
    TGender gender;
};

const int MAX = 100;
struct TList {
    TPerson person[MAX];
    short int size = -1;
};;

void AddPerson(TList &list, const TPerson &person)
{
    if (list.size < MAX - 1) 
    {
        list.size++;
        list.person[list.size] = person;
    } 
    else {
        cerr << "List is full, cannot add more persons." << endl;
    }
}

void printList(const TList& list)
{
    for (int i = 0; i <= list.size; i++) 
    {
        cout << "Name: " << list.person[i].name
            << ", Age: " << list.person[i].age << endl;
    }
}

int main()
{
    /* ofstream to create files */

	//TPerson person = { "John Doe", 65, OTHER };
	//ofstream file("person.dat", ios::binary | ios::app);

 //   if (file.is_open())
 //   {
 //       file.write(reinterpret_cast<const char*>(&person), sizeof(person));
 //       file.close();
	//	cout << "Data written to file successfully." << endl;
 //   }
 //   else
 //   {
 //       cerr << "Error opening file for writing." << endl;
	//	return 1;
 //   }

    /* ifstream to read files */

	TList list;
    TPerson person;
	ifstream file("person.dat", ios::binary | ios::in);

    if (file.is_open())
    {
        while (file.read(reinterpret_cast<char*>(&person), sizeof(person)))
            AddPerson(list, person);
        file.close();
        printList(list);
    }
    else
    {
        cout << "Error opening file for reading." << endl;
	}
}
