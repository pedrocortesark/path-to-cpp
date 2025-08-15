export module ManagePerson;

#include <string>;
#include <iostream>;

using namespace std;

const int MAX_SIZE = 50;
export struct Chain {
	char cadena[MAX_SIZE];
	int size = -1;
};

Chain strtoChain(const string& str)
{
	Chain chain;
	for (char c : str)
	{
		chain.size++;
		chain.cadena[chain.size] = c;
	}
	return chain;
}

string chainToStr(const Chain& chain)
{
	string str;
	for (int i = 0; i <= chain.size; i++)
		str += chain.cadena[i];

	return str;
}

export enum TGender { MALE, FEMALE, OTHER };

export struct TPerson {
	Chain doc, name, lastName;
	short unsigned age;
	TGender gender;
};

export TPerson createPerson(const string& doc, const string& name, const string& lastName, short unsigned int& age, const TGender& gender)
{
	TPerson person = { strtoChain(doc), strtoChain(name), strtoChain(lastName), age, gender };
	return person;
}

export string getName(const TPerson& person)
{
	return chainToStr(person.name);
}

export string getLastName(const TPerson& person)
{
	return chainToStr(person.lastName);
}

export string getDoc(const TPerson& person)
{
	return chainToStr(person.doc);
}

export short unsigned int getAge(const TPerson& person)
{
	return person.age;
}

export TGender getGender(const TPerson& person)
{
	return person.gender;
}

export void setName(TPerson& person, const string& name)
{
	person.name = strtoChain(name);
}

export void setLastName(TPerson& person, const string& lastName)
{
	person.lastName = strtoChain(lastName);
}

export void setDoc(TPerson& person, const string& doc)
{
	person.doc = strtoChain(doc);
}

export void setAge(TPerson& person, short unsigned int age)
{
	person.age = age;
}

export void setGender(TPerson& person, const TGender gender)
{
	person.gender = gender;
}

export string personToString(const TPerson& person)
{
	return "Doc: " + getDoc(person) + ", Name: " + getName(person) + ", Last Name: " + getLastName(person) + ", Age: " + to_string(getAge(person)) + ", Gender: " + to_string(getGender(person));
}

export const int LIST_LENGTH = 100;

export struct TList {
	TPerson persons[LIST_LENGTH];
	int count = -1;
};

export TList createList()
{
	TList list;
	return list;
}

export bool isEmpty(const TList& list)
{
	return list.count == -1;
}

export bool isFull(const TList& list)
{
	return list.count == LIST_LENGTH - 1;
}

/**
	@brief CONDITION: The list must not be full.
    @param list   - 
    @param person - 
**/
export void addPerson(TList& list, const TPerson& person)
{
	if (isFull(list)) return;

	list.count++;
	list.persons[list.count] = person;
}

export bool existsPerson(const TList& list, const string& doc, int &index)
{
	index = -1;
	for (int i = 0; i <= list.count; i++) {
		if (getDoc(list.persons[i]) == doc) {
			index = i;
			return true;
		}
	}
	return false;
}

/**
	@brief  PRECONDITION: The person exists in the list.
    @param  list  - 
    @param  doc   - 
    @param  index - 
    @retval       - 
**/
export TPerson seekPerson(const TList& list, const string& doc, const int& index = -1)
{
	if (index == -1)
	{
		for (int i = 0; i <= list.count; i++) {
			if (getDoc(list.persons[i]) == doc) {
				return list.persons[i];
			}
		}
	}
	else
	{
		return list.persons[index];
	}
}

export bool seekPerson(const TList& list, const string& doc, TPerson& person)
{
	for (int i = 0; i <= list.count; i++) {
		if (getDoc(list.persons[i]) == doc) {
			person = list.persons[i];
			return true;
		}
	}
	return false;
}

export void printList(const TList& l)
{
	for (int i = 0; i <= l.count; i++) {
		const TPerson& person = l.persons[i];
		cout << personToString(person) << endl;
	}
}