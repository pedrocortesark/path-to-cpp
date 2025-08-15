export module Person;

#include <string>;

using namespace std;

export enum TGender { MALE, FEMALE, OTHER };

export struct TPerson {
	string doc, name, lastName;
	short unsigned age;
	TGender gender;
};

export TPerson createPerson(const string& doc, const string& name, const string& lastName, short unsigned int& age, const TGender& gender)
{
	TPerson person = { doc, name, lastName, age, gender };
}

export string getName(const TPerson& person)
{
	return person.name;
}

export string getLastName(const TPerson& person)
{
	return person.lastName;
}

export string getDoc(const TPerson& person)
{
	return person.doc;
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
	person.name = name;
}

export void setLastName(TPerson& person, const string& lastName)
{
	person.lastName = lastName;
}

export void setDoc(TPerson& person, const string& doc)
{
	person.doc = doc;
}

export void setAge(TPerson& person, short unsigned int age)
{
	person.age = age;
}

export void setGender(TPerson& person, const TGender gender)
{
	person.gender = gender;
}